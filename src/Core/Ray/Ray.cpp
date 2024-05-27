/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

namespace Raytracer {
    Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
        : _origin(origin), _direction(direction), _time(0)
    {
    }

    Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction, double time)
        : _origin(origin), _direction(direction), _time(time)
    {
    }
} // namespace Raytracer
