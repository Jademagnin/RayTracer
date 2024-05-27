/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Noise
*/

#include "Noise.hpp"

namespace Raytracer {
    Color Noise::value(double u, double v, const Math::Point3D &p) const
    {
        (void)u;
        (void)v;
        return Color(.5, .5, .5) * (1 + sin(scale * p.z() + 10 * noise.turbulence(p, 7)));
    }
}
