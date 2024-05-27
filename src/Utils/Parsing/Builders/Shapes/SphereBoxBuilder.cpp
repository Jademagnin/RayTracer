/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBoxBuilder
*/

#include "SphereBoxBuilder.hpp"

std::shared_ptr<Hittable> SphereBoxBuilder::build(const libconfig::Setting &setting)
{
    const Point3D center = buildVector(SETTING("center"), {"x", "y", "z"});
    double cube_size = SETTING("cube_size");
    double sphere_radius = SETTING("sphere_radius");
    double scale = getScale(setting);

    // Scale point1 relative to point0
    cube_size *= scale;
    sphere_radius *= scale;

    return std::make_shared<SphereBox>(
        center,
        cube_size,
        sphere_radius,
        _materialBuilder.build(SETTING("material"))
    );
}
