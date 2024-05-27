/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** constants
*/

#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <limits>

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// assets
#define ASSETS_PATH "assets/"
#define TEXTURES_PATH ASSETS_PATH "textures/"

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
    return int(random_double(min, max + 1));
}
