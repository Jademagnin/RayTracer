/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HittableList
*/

#pragma once

#include "IHittable.hpp"
#include "Constants.hpp"
#include "Interval.hpp"
#include "Intersection.hpp"

#include <vector>

namespace Raytracer {
    /**
     * @class HittableList
     * @brief Class representing a list of hittable objects.
     */
    class HittableList : public Hittable {
        public:
            /**
             * @brief Construct a new HittableList object
             */
            HittableList() {}

            /**
             * @brief Construct a new HittableList object
             * 
             * @param object Object to add to the list
             */
            HittableList(shared_ptr<Hittable> object) { add(object); }

            /**
             * @brief Clear the list of objects
             */
            void clear() { objects.clear(); }

            /**
             * @brief Add an object to the list
             * 
             * @param object Object to add
             */
            void add(shared_ptr<Hittable> object);

            /**
             * @brief Check if a ray hits any object in the list
             * 
             * @param ray Ray to check
             * @param interval Interval of the ray
             * @param record Record of the hit
             * @return true If the ray hits any object
             * @return false Otherwise
             */
            bool hit(const Ray &ray, Interval interval,
                HitRecord &record) const override;

            /**
             * @brief Get the bounding box of the list of objects
             * 
             * @return Intersection Bounding box of the list
             */
            Intersection boundingBox() const override { return _bbox; }

        public:
            std::vector<shared_ptr<Hittable>> objects; ///< List of objects

        protected:
        private:
            Intersection _bbox; ///< Bounding box of the list
    };
} // namespace Raytracer
