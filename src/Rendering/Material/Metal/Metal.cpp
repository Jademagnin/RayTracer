/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Metal
*/

#include "Metal.hpp"

namespace Raytracer {
    bool Metal::scatter(const Ray &ray, const HitRecord &record,
        Color &attenuation, Ray &scattered) const
    {
        Math::Vector3D reflected = reflect(ray.direction(), record.normal);
        reflected = unit_vector(reflected) + (_fuzz * Math::random_unit_vector());
        scattered = Ray(record.point, reflected, ray.time());
        attenuation = _albedo;
        return (dot(scattered.direction(), record.normal) > 0);
    }
}
