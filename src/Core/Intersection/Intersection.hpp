/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Intersection
*/

#pragma once

#include "Ray.hpp"
#include "Interval.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @class Intersection
     * @brief Class representing an intersection in 3D space.
     */
    class Intersection {
        public:
            /**
             * @brief Construct a new Intersection object with default parameters
             */
            Intersection();

            /**
             * @brief Construct a new Intersection object
             * 
             * @param x Interval on the x-axis
             * @param y Interval on the y-axis
             * @param z Interval on the z-axis
             */
            Intersection(const Interval &x, const Interval &y, const Interval &z);

            /**
             * @brief Construct a new Intersection object
             * 
             * @param a First point of the intersection
             * @param b Second point of the intersection
             */
            Intersection(const Math::Point3D &a, const Math::Point3D &b);

            /**
             * @brief Construct a new Intersection object
             * 
             * @param box0 First intersection box
             * @param box1 Second intersection box
             */
            Intersection(const Intersection &box0, const Intersection &box1);

            /**
             * @brief Destroy the Intersection object
             */
            ~Intersection();

            /**
             * @brief Get the interval on a specific axis
             * 
             * @param axis Axis to get the interval from
             * @return const Interval& Interval on the specified axis
             */
            const Interval& axisInterval (int axis) const;

            /**
             * @brief Check if a ray hits the intersection
             * 
             * @param ray Ray to check
             * @param t Interval of the ray
             * @return true If the ray hits the intersection
             * @return false Otherwise
             */
            bool hit(const Ray &ray, Interval t) const;

            /**
             * @brief Get the longest axis of the intersection
             * 
             * @return int Longest axis of the intersection
             */
            int longestAxis() const;

        public:
            Interval x, y, z; ///< Intervals on the x, y, and z axes

            static const Intersection empty, universe; ///< Empty and universe intersections

        protected:
        private:
            /**
             * @brief Pad the intersection to the minimum size
             */
            void pad_to_min();
    };

    /**
     * @brief Add an offset to an intersection
     * 
     * @param a Intersection to add the offset to
     * @param offset Offset to add
     * @return Intersection Intersection with the added offset
     */
    Intersection operator+(const Intersection &a, const Math::Vector3D &offset);

    /**
     * @brief Add an offset to an intersection
     * 
     * @param offset Offset to add
     * @param a Intersection to add the offset to
     * @return Intersection Intersection with the added offset
     */
    Intersection operator+(const Math::Vector3D &offset, const Intersection &a);
} // namespace Raytracer
