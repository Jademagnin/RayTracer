/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Lambertian
*/

#include "Lambertian.hpp"

namespace Raytracer {
    bool Lambertian::scatter(const Ray &ray, const HitRecord &record,
        Color &attenuation, Ray &scattered) const
    {
        (void)ray;
        auto scatter_direction = record.normal + Math::random_unit_vector();

        if (scatter_direction.nearZero())
            scatter_direction = record.normal;

        scattered = Ray(record.point, scatter_direction, ray.time());
        attenuation = _texture->value(record.u, record.v, record.point);
        return true;
    };
}
