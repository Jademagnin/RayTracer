/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Translation
*/

#pragma once

#include "Hittable.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @class Translation
     * @brief Class representing a translation in 3D space.
     */
    class Translation : public Hittable {
        public:
            /**
             * @brief Construct a new Translation object
             * 
             * @param object Object to translate
             * @param offset Offset of the translation
             */
            Translation(std::shared_ptr<Hittable> object, const Math::Vector3D &offset);

            /**
             * @brief Check if a ray hits the translated object
             * 
             * @param ray Ray to check
             * @param t Interval of the ray
             * @param rec Record of the hit
             * @return true If the ray hits the translated object
             * @return false Otherwise
             */
            bool hit(const Ray &ray, Interval t, HitRecord &rec) const override;

            /**
             * @brief Get the bounding box of the translated object
             * 
             * @return Intersection Bounding box of the translated object
             */
            Intersection boundingBox() const override { return bbox; }

        private:
            std::shared_ptr<Hittable> _object; ///< Object to translate
            Math::Vector3D _offset; ///< Offset of the translation
            Intersection bbox; ///< Bounding box of the translated object
    };
} // namespace Raytracer
