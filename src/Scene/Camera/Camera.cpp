/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Raytracer {
    std::optional<Cluster> Camera::getNextCluster()
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        if (_workQueue.empty()) {
            return {};
        }
        auto cluster = _workQueue.front();
        _workQueue.pop();
        return cluster;
    }

    std::vector<Cluster> Camera::getNextClusters()
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        std::vector<Cluster> clusters;
        for (int i = 0; i < _cluster_size && !_workQueue.empty(); ++i) {
            clusters.push_back(_workQueue.front());
            _workQueue.pop();
        }
        return clusters;
    }

    void Camera::initThreads()
    {
        _pixelsCompleted = 0;
        _total_pixels = image_width * image_height;
        _pixels.resize(image_height, std::vector<Color>(image_width));
        _numThreads = std::max(std::thread::hardware_concurrency(), 1u);
        _cluster_size = std::sqrt(_total_pixels / _numThreads);

        // Increase the cluster size to reduce the number of tasks.
        _cluster_size *= 2;

        for (int j = 0; j < image_height; j += _cluster_size) {
            for (int i = 0; i < image_width; i += _cluster_size) {
                _workQueue.push({i, j});
            }
        }
    }

    std::optional<std::string> Camera::estimateRemainingTime()
    {
        int newPercentage = int(100.0 * this->_pixelsCompleted / this->_total_pixels);
        if (newPercentage <= _percentage)
            return {};
        _percentage = newPercentage;
        _percentageTimes.push_back(std::chrono::high_resolution_clock::now());
        auto averageTime = (std::chrono::duration_cast<std::chrono::milliseconds>(
            (_percentageTimes.back() - _startTime) / _percentageTimes.size()) * 1.7
        ).count();

        auto remainingTime = static_cast<int>(averageTime * (100 -
            _percentage) / 1000.0);
        std::string timeUnit = "s";
        int remainingMinutes = 0;
        if (remainingTime >= 60) {
            remainingMinutes = remainingTime % 60;
            remainingTime /= 60;
            timeUnit = "m";
            if (remainingTime >= 60) {
                remainingTime /= 60;
                timeUnit = "h";
            }
        }
        std::string result = std::to_string(remainingTime) + timeUnit;
        if (timeUnit == "h") {
            result += std::to_string(remainingMinutes) + "m";
        }
        return result;
    }

    void Camera::renderPixel(int i, int j)
    {
        Color pixel_color(0,0,0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
            Ray r = getRay(i, j);
            pixel_color += rayColor(r, max_depth, *this->_world);
        }
        this->_pixels[j][i] = _pixel_samples_scale * pixel_color;
        ++this->_pixelsCompleted;

        std::optional<std::string> remainingTime = estimateRemainingTime();
        if (!remainingTime.has_value())
            return;

        static int lastPercentage = -1;
        if (_percentage != lastPercentage) {
            lastPercentage = _percentage;

            std::lock_guard<std::mutex> lock(this->_clogMutex);
            std::clog << std::string(80, ' ');
            std::clog << "\rRendering: " << _percentage << "%, estimated time remaining: "
                << remainingTime.value();
        }
    }

    void Camera::renderClusters()
    {
        ThreadPool pool(_numThreads);

        for (auto clusters = this->getNextClusters(); !clusters.empty();
             clusters = this->getNextClusters())
        {
            for (const auto& cluster : clusters)
            {
                pool.enqueue([this, cluster] {
                    auto [iStart, jStart] = cluster;
                    for (int j = jStart; j < std::min(jStart + this->_cluster_size,
                        image_height); j++) {
                        for (int i = iStart; i < std::min(iStart + this->_cluster_size,
                            image_width); i++)
                            renderPixel(i, j);
                    }
                });
            }
        }
    }

    void Camera::writePPM() const
    {
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (const auto& row : _pixels) {
            for (const auto& pixel : row) {
                write_color(std::cout, pixel);
            }
        }

        std::clog << "\rDone.                                              \n";
    }

    void Camera::render(const Hittable &world)
    {
        _startTime = std::chrono::high_resolution_clock::now();
        _world = &world;
        initCamera();
        initThreads();
        renderClusters();
        writePPM();
    }

    void Camera::initCamera()
    {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        _pixel_samples_scale = 1.0 / samples_per_pixel;

        _center = origin;

        // Determine viewport dimensions.
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focus_distance;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        _w = unit_vector(origin - direction);
        _u = unit_vector(cross(vup, _w));
        _v = cross(_w, _u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        Math::Vector3D viewport_u = viewport_width * _u;
        Math::Vector3D viewport_v = viewport_height * -_v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        _pixel_delta_u = viewport_u / image_width;
        _pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = _center - (focus_distance * _w)
                                - viewport_u / 2 - viewport_v / 2;
        _pixel00_loc = viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
        auto defocus_radius = focus_distance * tan(degrees_to_radians(defocus_angle / 2));
        _defocus_disk_u = _u * defocus_radius;
        _defocus_disk_v = _v * defocus_radius;
    }

    // Raytracing
    Color Camera::rayColor(const Ray &ray, int depth, const Hittable &world) const
    {
        if (depth <= 0)
            return Color(0, 0, 0);
        HitRecord record;

        if (!world.hit(ray, Interval(0.001, infinity), record)) {
            return background;
        }

        Ray scattered;
        Color attenuation;
        Color color_from_emission = record.material->emitted(record.u, record.v, record.point);

        if (!record.material->scatter(ray, record, attenuation, scattered))
            return color_from_emission;

        Color color_from_scatter = attenuation * rayColor(scattered, depth - 1, world);

        return color_from_emission + color_from_scatter;

        // if (world.hit(ray, Interval(0.001, infinity), record)) {
        //     Ray scattered;
        //     Color attenuation;
        //     if (record.material->scatter(ray, record, attenuation, scattered))
        //         return attenuation * rayColor(scattered, depth - 1, world);
        //     return Color(0, 0, 0);
        // }

        // Math::Vector3D unit_direction = unit_vector(ray.direction());
        // auto a = 0.5 * (unit_direction.y() + 1.0);
        // return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

    Ray Camera::getRay(int i, int j) const
    {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sampleSquare();
        auto pixel_sample = _pixel00_loc
                          + ((i + offset.x()) * _pixel_delta_u)
                          + ((j + offset.y()) * _pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? _center : defocusDiskSample();
        auto ray_direction = pixel_sample - ray_origin;
        auto ray_time = random_double();

        return Ray(ray_origin, ray_direction, ray_time);
    }

    Math::Vector3D Camera::sampleSquare() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Math::Vector3D(random_double() - 0.5, random_double() - 0.5, 0);
    }

    Math::Point3D Camera::defocusDiskSample() const
    {
        // Returns a random point in the camera defocus disk.
        auto p = Math::random_in_unit_disk();
        return _center + (p[0] * _defocus_disk_u) + (p[1] * _defocus_disk_v);
    }
}
