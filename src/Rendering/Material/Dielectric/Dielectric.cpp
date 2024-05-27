/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Dielectric
*/

#include "Dielectric.hpp"

namespace Raytracer {
    bool Dielectric::scatter(const Ray &ray, const HitRecord &record,
        Color &attenuation, Ray &scattered) const
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = record.front_face ? (1.0/refraction_index) : refraction_index;

        Math::Vector3D unit_direction = Math::unit_vector(ray.direction());
        double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        Math::Vector3D direction;

        direction = (cannot_refract || reflectance(cos_theta, ri) > random_double())
                    ? reflect(unit_direction, record.normal)
                    : refract(unit_direction, record.normal, ri);

        scattered = Ray(record.point, direction, ray.time());
        return true;
    };
}
