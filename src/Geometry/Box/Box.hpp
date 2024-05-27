/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Box
*/

#pragma once

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Intersection.hpp"
#include "Hittable.hpp"
#include "Geometry.hpp"

namespace Raytracer {
    using namespace Math;
    using namespace Raytracer;

    /**
     * @brief Creates a box as a list of planes (Hittable objects)
     * 
     * @param p0 One corner of the box
     * @param p1 The opposite corner of the box
     * @param mat Material of the box
     * @return shared_ptr<HittableList> List of planes forming the box
     */
    inline shared_ptr<HittableList> Box(const Point3D &p0, const Point3D &p1, shared_ptr<Material> mat)
    {
        auto sides = make_shared<HittableList>();

        auto min = Point3D(fmin(p0.x(), p1.x()), fmin(p0.y(), p1.y()), fmin(p0.z(), p1.z()));
        auto max = Point3D(fmax(p0.x(), p1.x()), fmax(p0.y(), p1.y()), fmax(p0.z(), p1.z()));

        auto dx = Vector3D(max.x() - min.x(), 0, 0);
        auto dy = Vector3D(0, max.y() - min.y(), 0);
        auto dz = Vector3D(0, 0, max.z() - min.z());

        sides->add(make_shared<Plane>(Point3D(min.x(), min.y(), max.z()), dx, dy, mat)); // front
        sides->add(make_shared<Plane>(Point3D(max.x(), min.y(), max.z()), -dz, dy, mat)); // right
        sides->add(make_shared<Plane>(Point3D(max.x(), min.y(), min.z()), -dx, dy, mat)); // back
        sides->add(make_shared<Plane>(Point3D(min.x(), min.y(), min.z()), dz, dy, mat)); // left
        sides->add(make_shared<Plane>(Point3D(min.x(), max.y(), max.z()), dx, -dz, mat)); // top
        sides->add(make_shared<Plane>(Point3D(min.x(), min.y(), min.z()), dx, dz, mat)); // bottom

        return sides;
    }
}
