/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#pragma once

#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @class Ray
     * @brief Class representing a ray in 3D space.
     */
    class Ray {
        public:
            /**
             * @brief Construct a new Ray object with default parameters
             */
            Ray() = default;

            /**
             * @brief Construct a new Ray object
             * 
             * @param origin Origin of the ray
             * @param direction Direction of the ray
             */
            Ray(const Math::Point3D &origin, const Math::Vector3D &direction);

            /**
             * @brief Construct a new Ray object
             * 
             * @param origin Origin of the ray
             * @param direction Direction of the ray
             * @param time Time at which the ray exists
             */
            Ray(const Math::Point3D &origin, const Math::Vector3D &direction, double time);

            /**
             * @brief Destroy the Ray object
             */
            ~Ray() = default;

            /**
             * @brief Copy constructor
             * 
             * @param ray The ray to copy
             */
            Ray(const Ray &ray) = default;

            /**
             * @brief Move constructor
             * 
             * @param ray The ray to move
             */
            Ray(Ray &&ray) = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param ray The ray to copy
             * @return Ray& Reference to the copied ray
             */
            Ray &operator=(const Ray &ray) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param ray The ray to move
             * @return Ray& Reference to the moved ray
             */
            Ray &operator=(Ray &&ray) = default;

            /**
             * @brief Set the Origin of the ray
             * 
             * @param origin New origin of the ray
             */
            void setOrigin(const Math::Point3D &origin) { _origin = origin; }

            /**
             * @brief Set the Direction of the ray
             * 
             * @param direction New direction of the ray
             */
            void setDirection(const Math::Vector3D &direction) { _direction = direction; }

        public:
            /**
             * @brief Get the Origin of the ray
             * 
             * @return const Math::Point3D& Origin of the ray
             */
            const Math::Point3D &origin() const { return _origin; }

            /**
             * @brief Get the Direction of the ray
             * 
             * @return const Math::Vector3D& Direction of the ray
             */
            const Math::Vector3D &direction() const { return _direction; }

            /**
             * @brief Get the point at a certain distance along the ray
             * 
             * @param t Distance along the ray
             * @return Math::Point3D Point at distance t along the ray
             */
            Math::Point3D pointAt(double t) const { return _origin + t * _direction; }

            /**
             * @brief Get the Time at which the ray exists
             * 
             * @return double Time at which the ray exists
             */
            double time() const { return _time; }

        protected:
        private:
            Math::Point3D _origin; ///< Origin of the ray
            Math::Vector3D _direction; ///< Direction of the ray
            double _time; ///< Time at which the ray exists
    };
} // namespace Raytracer
