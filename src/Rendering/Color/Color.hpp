/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#pragma once

#include "Vector3D.hpp"
#include "Interval.hpp"

namespace Raytracer {
    using Color = Math::Vector3D;

    void write_color(std::ostream &out, const Color &pixel_color);
    inline double linear_to_gamma(double x);
}
