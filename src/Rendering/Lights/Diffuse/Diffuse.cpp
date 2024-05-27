/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Diffuse
*/

#include "Diffuse.hpp"

namespace Raytracer {
    Color Diffuse::emitted(double u, double v, const Math::Point3D &p) const
    {
        (void)u;
        (void)v;
        (void)p;
        return _texture->value(u, v, p);
    }
}
