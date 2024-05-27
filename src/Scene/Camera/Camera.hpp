/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#pragma once

#include "IHittable.hpp"
#include "Color.hpp"
#include "Vector3D.hpp"
#include "Utils.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <optional>
#include <chrono>

namespace Raytracer {
    using Cluster = std::pair<int, int>;
    /**
     * @brief A class that represents a camera in the raytracer.
     */
    class Camera {
        public:
            Camera() = default;
            Camera(const Camera &camera) = default;
            Camera(Camera &&camera) = default;
            /**
             * @brief Copy assignment operator.
             * 
             * @param camera The camera to copy.
             * @return Camera& A reference to the copied camera.
             */
            Camera &operator=(const Camera &camera) {
                if (this == &camera)
                    return *this;
                aspect_ratio = camera.aspect_ratio;
                image_width = camera.image_width;
                samples_per_pixel = camera.samples_per_pixel;
                max_depth = camera.max_depth;
                background = camera.background;
                vfov = camera.vfov;
                origin = camera.origin;
                direction = camera.direction;
                vup = camera.vup;
                defocus_angle = camera.defocus_angle;
                focus_distance = camera.focus_distance;
                return *this;
            }
            Camera &operator=(Camera &&camera) = default;
            ~Camera() = default;

        public:
            /**
             * @brief Render the world from the perspective of the camera.
             * 
             * @param world The world to render.
             */
            void render(const Hittable &world);
        public:
            double aspect_ratio = 1.0;
            int image_width = 100;
            int samples_per_pixel = 10;
            int max_depth = 10; // Max ray bounce in the scene
            Color background;

            double vfov = 90.0;
            Math::Point3D origin = Math::Point3D(0, 0, 0);
            Math::Vector3D direction = Math::Vector3D(0, 0, -1);
            Math::Vector3D vup = Math::Vector3D(0, 1, 0);

            double defocus_angle = 0.0;
            double focus_distance = 10.0;

        private:
            void initCamera();
            Color rayColor(const Ray &ray, int depth, const Hittable &world) const;
            Ray getRay(int i, int j) const;
            Math::Vector3D sampleSquare() const;
            Math::Point3D defocusDiskSample() const;
            std::optional<std::string> estimateRemainingTime();

            // Threading
            void initThreads();
            int totalPixels() const { return image_width * image_height; }
            int clusterSize() const { return std::sqrt(totalPixels() / _numThreads); }
            std::optional<Cluster> getNextCluster();
            std::vector<Cluster> getNextClusters();
            void renderClusters();
            void writePPM() const;
            void renderPixel(int i, int j);
        private:
            const Hittable *_world;
            int image_height;
            Math::Point3D _center;
            Math::Point3D _pixel00_loc;
            Math::Vector3D _pixel_delta_u;
            Math::Vector3D _pixel_delta_v;
            double _pixel_samples_scale;
            Math::Vector3D _u, _v, _w;
            Math::Vector3D _defocus_disk_u, _defocus_disk_v;

            // Multi-threading and clustering
            size_t _numThreads = std::thread::hardware_concurrency();
            std::queue<Cluster> _workQueue;
            std::mutex _queueMutex;

            int _percentage = 0;
            int _cluster_size = 0;
            int _total_pixels = 0;
            std::atomic<int> _pixelsCompleted = 0;
            std::vector<std::vector<Color>> _pixels;
            std::mutex _clogMutex;
            std::vector<std::chrono::high_resolution_clock::time_point> _percentageTimes;
            std::chrono::high_resolution_clock::time_point _startTime;
    };
}
