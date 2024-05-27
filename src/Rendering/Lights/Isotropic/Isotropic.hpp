/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Isotropic
*/

#pragma once

#include "Material.hpp"
#include "Texture.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents an isotropic material in the raytracer.
     */
    class Isotropic : public Material {
        public:
            /**
             * @brief Construct a new Isotropic object with a given color.
             * 
             * @param color The color of the isotropic material.
             */
            Isotropic(const Color &color);
            /**
             * @brief Construct a new Isotropic object with a given texture.
             * 
             * @param tex The texture of the isotropic material.
             */
            Isotropic(shared_ptr<Texture> tex);

        public:
            /**
             * @brief Determine if a ray scatters off the isotropic material.
             * 
             * @param ray The ray to check.
             * @param rec The hit record to fill.
             * @param attenuation The attenuation of the ray.
             * @param scattered The scattered ray.
             * @return true If the ray scatters.
             * @return false Otherwise.
             */
            bool scatter(const Ray &ray, const HitRecord &rec, Color &attenuation, Ray &scattered) const override;

        private:
            shared_ptr<Texture> _tex; ///< The texture of the isotropic material.
    };
} // namespace Raytracer
