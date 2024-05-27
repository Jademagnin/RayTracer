/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Density
*/

#pragma once

#include "Hittable.hpp"
#include "Lights.hpp"
#include "Material.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a density in the raytracer.
     */
    class Density : public Hittable {
        public:
            /**
             * @brief Construct a new Density object with a given boundary, density, and texture.
             * 
             * @param boundary The boundary of the density.
             * @param density The density value.
             * @param tex The texture of the density.
             */
            Density(shared_ptr<Hittable> boundary, double density, shared_ptr<Texture> tex);
            /**
             * @brief Construct a new Density object with a given boundary, density, and color.
             * 
             * @param boundary The boundary of the density.
             * @param density The density value.
             * @param color The color of the density.
             */
            Density(shared_ptr<Hittable> boundary, double density, const Color &color);

        public:
            /**
             * @brief Determine if a ray hits the density.
             * 
             * @param ray The ray to check.
             * @param t The interval to check.
             * @param rec The hit record to fill.
             * @return true If the ray hits the density.
             * @return false Otherwise.
             */
            bool hit(const Ray &ray, Interval t, HitRecord &rec) const override;
            /**
             * @brief Get the bounding box of the density.
             * 
             * @return Intersection The bounding box of the density.
             */
            Intersection boundingBox() const override { return _boundary->boundingBox(); }

        private:
            shared_ptr<Hittable> _boundary; ///< The boundary of the density.
            double _density; ///< The density value.
            shared_ptr<Material> _phaseFunction; ///< The phase function of the density.
    };
} // namespace Raytracer