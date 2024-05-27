/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Solid
*/

#pragma once

#include "ATexture.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a solid texture in the raytracer.
     */
    class Solid : public Texture {
        public:
            Solid() = default;
            /**
             * @brief Construct a new Solid object with a given color.
             * 
             * @param albedo The color of the solid.
             */
            Solid(const Color &albedo);
            /**
             * @brief Construct a new Solid object with a given color.
             * 
             * @param r The red component of the color.
             * @param g The green component of the color.
             * @param b The blue component of the color.
             */
            Solid(double r, double g, double b);
            ~Solid() = default;

            Solid(const Solid &other) = default;
            Solid(Solid &&other) = default;
            Solid &operator=(const Solid &other) = default;
            Solid &operator=(Solid &&other) = default;

            /**
             * @brief Get the color of the solid at a given point.
             * 
             * @param u The u coordinate of the point.
             * @param v The v coordinate of the point.
             * @param p The 3D point.
             * @return Color The color of the solid at the point.
             */
            Color value(double u, double v, const Math::Point3D &p) const override {
                (void)u;
                (void)v;
                (void)p;

                return _albedo;
            }

        protected:
        private:
            Color _albedo; ///< The color of the solid.
    };
}
