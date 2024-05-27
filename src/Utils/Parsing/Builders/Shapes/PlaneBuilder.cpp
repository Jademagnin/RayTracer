/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlaneBuilder
*/

#include "PlaneBuilder.hpp"

std::shared_ptr<Hittable> PlaneBuilder::build(const libconfig::Setting &setting)
{
    const Point3D origin = buildVector(SETTING("origin"), {"x", "y", "z"});
    Vector3D direction_u = buildVector(SETTING("direction_u"), {"x", "y", "z"});
    Vector3D direction_v = buildVector(SETTING("direction_v"), {"x", "y", "z"});
    double scale = getScale(setting);

    // Scale direction_u and direction_v
    direction_u *= scale;
    direction_v *= scale;

    return std::make_shared<Plane>(
        origin,
        direction_u,
        direction_v,
        _materialBuilder.build(SETTING("material"))
    );
}
