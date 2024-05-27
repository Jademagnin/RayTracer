/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBuilder
*/

#include "SphereBuilder.hpp"

std::shared_ptr<Hittable> SphereBuilder::build(const libconfig::Setting &setting)
{
    double scale = getScale(setting);
    double radius = static_cast<double>(SETTING("radius")) * scale;

    if (!setting.exists("center2")) {
        return (std::make_shared<Sphere>(
            buildVector(SETTING("center"), {"x", "y", "z"}),
            radius, _materialBuilder.build(SETTING("material"))
        ));
    } else {
        return (std::make_shared<Sphere>(
            buildVector(SETTING("center"), {"x", "y", "z"}),
            buildVector(SETTING("center2"), {"x", "y", "z"}),
            radius, _materialBuilder.build(SETTING("material"))
        ));
    }
}
