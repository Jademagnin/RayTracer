/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rotation
*/

#pragma once

#include "Hittable.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @class Rotation
     * @brief Class representing a rotation in 3D space.
     */
    class Rotation : public Hittable {
        public:
            /**
             * @brief Construct a new Rotation object
             * 
             * @param object Object to rotate
             * @param angle Angle of the rotation
             */
            Rotation(std::shared_ptr<Hittable> object, double angle);

            /**
             * @brief Check if a ray hits the rotated object
             * 
             * @param ray Ray to check
             * @param t Interval of the ray
             * @param rec Record of the hit
             * @return true If the ray hits the rotated object
             * @return false Otherwise
             */
            bool hit(const Ray &ray, Interval t, HitRecord &rec) const override;

            /**
             * @brief Get the bounding box of the rotated object
             * 
             * @return Intersection Bounding box of the rotated object
             */
            Intersection boundingBox() const override { return bbox; }

        private:
            std::shared_ptr<Hittable> _object; ///< Object to rotate
            double sin_theta; ///< Sine of the rotation angle
            double cos_theta; ///< Cosine of the rotation angle
            Intersection bbox; ///< Bounding box of the rotated object
    };
} // namespace Raytracer
