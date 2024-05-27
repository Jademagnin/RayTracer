/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IMaterial
*/

#pragma once

#include "HitRecord.hpp"
#include "Color.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    class HitRecord;
    /**
     * @brief An interface for materials in the raytracer.
     */
    class IMaterial {
        public:
            /**
             * @brief Destroy the IMaterial object.
             */
            virtual ~IMaterial() = default;

        public:
            /**
             * @brief Scatter a ray off the material.
             * 
             * @param ray The incident ray.
             * @param hit The hit record of the ray with the material.
             * @param attenuation The attenuation of the scattered ray.
             * @param scattered The scattered ray.
             * @return true If the ray was scattered.
             * @return false Otherwise.
             */
            virtual bool scatter(const Ray &ray, const HitRecord &hit,
                Color &attenuation, Ray &scattered) const = 0;

            /**
             * @brief Get the emitted color of the material.
             * 
             * @param u The u coordinate of the point.
             * @param v The v coordinate of the point.
             * @param p The 3D point.
             * @return Color The emitted color.
             */
            virtual Color emitted(double u, double v, const Math::Point3D &p) const {
                (void)u;
                (void)v;
                (void)p;
                return Color(0, 0, 0);
            }

        public:

        protected:
        private:
    };
} // namespace Raytracer
