/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rotation
*/

#include "Rotation.hpp"

namespace Raytracer
{
    Rotation::Rotation(std::shared_ptr<Hittable> object, double angle)
        : _object(object)
    {
        auto radians = degrees_to_radians(angle);
        sin_theta = sin(radians);
        cos_theta = cos(radians);
        bbox = object->boundingBox();

        Math::Point3D min(+infinity, +infinity, +infinity);
        Math::Point3D max(-infinity, -infinity, -infinity);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++)
                {
                    auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
                    auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
                    auto z = k * bbox.z.max + (1 - k) * bbox.z.min;

                    auto newx = cos_theta * x + sin_theta * z;
                    auto newz = -sin_theta * x + cos_theta * z;

                    Math::Point3D tester(newx, y, newz);

                    for (int c = 0; c < 3; c++)
                    {
                        min[c] = fmin(min[c], tester[c]);
                        max[c] = fmax(max[c], tester[c]);
                    }
                }
            }
        }
        bbox = Intersection(min, max);
    }

    bool Rotation::hit(const Ray &ray, Interval t, HitRecord &rec) const
    {
        auto origin = ray.origin();
        auto direction = ray.direction();

        origin[0] = cos_theta * ray.origin()[0] - sin_theta * ray.origin()[2];
        origin[2] = sin_theta * ray.origin()[0] + cos_theta * ray.origin()[2];

        direction[0] = cos_theta * ray.direction()[0] - sin_theta * ray.direction()[2];
        direction[2] = sin_theta * ray.direction()[0] + cos_theta * ray.direction()[2];

        Ray rotated_ray(origin, direction, ray.time());

        if (!_object->hit(rotated_ray, t, rec))
            return false;

        auto p = rec.point;
        auto normal = rec.normal;

        p[0] = cos_theta * rec.point[0] + sin_theta * rec.point[2];
        p[2] = -sin_theta * rec.point[0] + cos_theta * rec.point[2];

        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

        rec.point = p;
        rec.setFaceNormal(rotated_ray, normal);

        return true;
    }
}