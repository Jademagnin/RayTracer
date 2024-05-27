/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Perlin
*/

#pragma once

#include "Vector3D.hpp"
#include "Texture.hpp"
#include "Perlin.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a noise texture in the raytracer.
     */
    class Noise : public Texture {
    public:
        /**
         * @brief Construct a new Noise object with default scale.
         */
        Noise() {}
        /**
         * @brief Construct a new Noise object with a given scale.
         * 
         * @param sc The scale of the noise.
         */
        Noise(double sc) : scale(sc) {}

        /**
         * @brief Get the color of the noise at a given point.
         * 
         * @param u The u coordinate of the point.
         * @param v The v coordinate of the point.
         * @param p The 3D point.
         * @return Color The color of the noise at the point.
         */
        Color value(double u, double v, const Math::Point3D &p) const override;

    protected:

    private:
        Perlin noise; ///< The Perlin noise generator.
        double scale; ///< The scale of the noise.

    };
}
