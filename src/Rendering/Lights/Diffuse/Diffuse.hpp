/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Diffuse
*/

#pragma once

#include "Material.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a diffuse material in the raytracer.
     */
    class Diffuse : public Material {
        public:
            /**
             * @brief Construct a new Diffuse object with a given texture.
             * 
             * @param tex The texture of the diffuse material.
             */
            Diffuse(shared_ptr<Texture> tex) : _texture(tex) {}
            /**
             * @brief Construct a new Diffuse object with a given color.
             * 
             * @param color The color of the diffuse material.
             */
            Diffuse(const Color &color) : _texture(make_shared<Solid>(color)) {}

        public:
            /**
             * @brief Get the color that the diffuse material emits at a given point.
             * 
             * @param u The u coordinate of the point.
             * @param v The v coordinate of the point.
             * @param p The 3D point.
             * @return Color The color that the diffuse material emits.
             */
            Color emitted(double u, double v, const Math::Point3D &p) const override;

        protected:
        private:
            shared_ptr<Texture> _texture; ///< The texture of the diffuse material.
    };
} // namespace Raytracer
