/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CylinderBuilder
*/

#include "CylinderBuilder.hpp"

std::shared_ptr<Hittable> CylinderBuilder::build(const libconfig::Setting &setting)
{
    const Point3D center = buildVector(SETTING("center"), {"x", "y", "z"});
    double radius = SETTING("radius");
    double height = SETTING("height");
    double scale = getScale(setting);

    // Scale radius and height
    radius *= scale;
    height *= scale;

    return std::make_shared<Cylinder>(
        center,
        radius,
        height,
        _materialBuilder.build(SETTING("material"))
    );
}
