/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Metal
*/

#pragma once

#include "Material.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"

namespace Raytracer {
    class HitRecord;
    /**
     * @brief A class that represents a metal material in the raytracer.
     */
    class Metal : public Material {
        public:
            /**
             * @brief Construct a new Metal object with a given albedo and fuzziness.
             * 
             * @param albedo The albedo of the metal.
             * @param fuzz The fuzziness of the metal.
             */
            Metal(const Color &albedo, double fuzz) : _albedo(albedo),
                                        _fuzz(fuzz < 1 ? fuzz : 1) {}
            /**
             * @brief Construct a new Metal object with default albedo and fuzziness.
             */
            Metal() = default;
            /**
             * @brief Destroy the Metal object.
             */
            ~Metal() = default;

            /**
             * @brief Scatter a ray off the metal.
             * 
             * @param ray The incident ray.
             * @param hit The hit record of the ray with the metal.
             * @param attenuation The attenuation of the scattered ray.
             * @param scattered The scattered ray.
             * @return true If the ray was scattered.
             * @return false Otherwise.
             */
            bool scatter(const Ray &ray, const HitRecord &hit,
                Color &attenuation, Ray &scattered) const override;

        protected:
        private:
            Color _albedo; ///< The albedo of the metal.
            double _fuzz; ///< The fuzziness of the metal.
    };
} // namespace Raytracer
