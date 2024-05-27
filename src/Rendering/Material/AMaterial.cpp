/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material
*/

#include "AMaterial.hpp"

namespace Raytracer {
    bool Material::scatter(const Ray &ray, const HitRecord &hit,
        Color &attenuation, Ray &scattered) const
    {
        (void)ray;
        (void)hit;
        (void)attenuation;
        (void)scattered;

        return false;
    }
}
