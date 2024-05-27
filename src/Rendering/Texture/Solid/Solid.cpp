/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Solid
*/

#include "Solid.hpp"

namespace Raytracer {
    Solid::Solid(const Color &albedo) : _albedo(albedo) {}
    Solid::Solid(double r, double g, double b) : Solid(Color(r, g, b)) {}
}