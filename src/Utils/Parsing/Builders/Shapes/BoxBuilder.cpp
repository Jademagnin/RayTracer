/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** BoxBuilder
*/

#include "BoxBuilder.hpp"

std::shared_ptr<Hittable> BoxBuilder::build(const libconfig::Setting &setting)
{
    const Point3D point0 = buildVector(SETTING("point0"), {"x", "y", "z"});
    Point3D point1 = buildVector(SETTING("point1"), {"x", "y", "z"});
    double scale = getScale(setting);

    // Scale point1 relative to point0
    point1 = point0 + (point1 - point0) * scale;

    return std::make_shared<BVHNode>(
        HittableList(
            Box(point0, point1, _materialBuilder.build(SETTING("material")))
        )
    );
}
