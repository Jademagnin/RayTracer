/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HitRecord
*/

#pragma once

#include "Ray.hpp"
#include "AMaterial.hpp"

namespace Raytracer {
    class Material;

    /**
     * @class HitRecord
     * @brief Class representing a record of a hit.
     */
    class HitRecord {
        public:
            /**
             * @brief Construct a new HitRecord object
             */
            HitRecord() = default;

            /**
             * @brief Construct a new HitRecord object
             * 
             * @param p Point of the hit
             * @param n Normal at the hit point
             * @param t Parameter at which the hit occurs
             */
            HitRecord(const Math::Point3D &p, const Math::Vector3D &n, double t)
                : point(p), normal(n), t(t) {}

            /**
             * @brief Destroy the HitRecord object
             */
            ~HitRecord() = default;

            /**
             * @brief Copy constructor
             * 
             * @param rec HitRecord to copy
             */
            HitRecord(const HitRecord &rec) = default;

            /**
             * @brief Move constructor
             * 
             * @param rec HitRecord to move
             */
            HitRecord(HitRecord &&rec) = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param rec HitRecord to copy
             * @return HitRecord& Reference to the copied HitRecord
             */
            HitRecord &operator=(const HitRecord &rec) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param rec HitRecord to move
             * @return HitRecord& Reference to the moved HitRecord
             */
            HitRecord &operator=(HitRecord &&rec) = default;

        public:
            /**
             * @brief Set the face normal
             * 
             * @param r Ray
             * @param outward_normal Outward normal
             */
            void setFaceNormal(const Ray &r, const Math::Vector3D &outward_normal);

        public:
            Math::Point3D point; ///< Point of the hit
            Math::Vector3D normal; ///< Normal at the hit point
            shared_ptr<Material> material; ///< Material of the hit object
            double t; ///< Parameter at which the hit occurs
            double u; ///< U coordinate of the hit
            double v; ///< V coordinate of the hit
            bool front_face; ///< Whether the hit was on the front face
    };
} // namespace Raytracer
