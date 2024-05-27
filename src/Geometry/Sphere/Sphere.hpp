/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "IHittable.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @class Sphere
     * @brief Class representing a sphere in 3D space.
     */
    class Sphere : public Hittable {
        public:
            /**
             * @brief Construct a new Sphere object
             * 
             * @param center Center of the sphere
             * @param radius Radius of the sphere
             * @param material Material of the sphere
             */
            Sphere(const Math::Point3D &center, double radius,
                shared_ptr<Material> material);

            /**
             * @brief Construct a new Sphere object
             * 
             * @param center Center of the sphere
             * @param center2 Second center for moving sphere
             * @param radius Radius of the sphere
             * @param material Material of the sphere
             */
            Sphere(const Math::Point3D &center, const Math::Vector3D &center2,
                double radius, shared_ptr<Material> material);

            /**
             * @brief Construct a new Sphere object with default parameters
             */
            Sphere() : _center1(Math::Point3D(0, 0, 0)), _radius(0),
                _material(nullptr) {}

            /**
             * @brief Set the Center object
             * 
             * @param center New center of the sphere
             */
            void setCenter(const Math::Point3D &center) { _center1 = center; }

            /**
             * @brief Set the Radius object
             * 
             * @param radius New radius of the sphere
             */
            void setRadius(double radius) { _radius = radius; }

            /**
             * @brief Set the Material object
             * 
             * @param material New material of the sphere
             */
            void setMaterial(shared_ptr<Material> material) { _material = material; }

            /**
             * @brief Determines if a ray hits the sphere
             * 
             * @param ray The ray to check
             * @param interval The interval to check within
             * @param record The hit record to fill with hit information
             * @return true If the ray hits the sphere
             * @return false Otherwise
             */
            bool hit(const Raytracer::Ray &ray, Interval interval,
                HitRecord &record) const override;

            /**
             * @brief Get the bounding box of the sphere
             * 
             * @return Intersection The bounding box
             */
            Intersection boundingBox() const override { return _bbox; }

        private:
            /**
             * @brief Get the center of the sphere at a given time
             * 
             * @param time The time at which to get the center
             * @return Math::Point3D The center of the sphere
             */
            Math::Point3D sphere_center(double time) const
            {
                return _center1 + time * _center_vector;
            }

            /**
             * @brief Get the UV coordinates on the sphere for a given point
             * 
             * @param p The point on the sphere
             * @param u The U coordinate to fill
             * @param v The V coordinate to fill
             */
            static void get_sphere_uv(const Math::Point3D &p, double &u, double &v)
            {
                auto theta = acos(-p.y());
                auto phi = atan2(-p.z(), p.x()) + M_PI;

                u = phi / (2 * M_PI);
                v = theta / M_PI;
            }

            Math::Point3D _center1;
            double _radius;
            shared_ptr<Material> _material;
            bool _is_moving;
            Math::Vector3D _center_vector;
            Intersection _bbox;
    };
}
