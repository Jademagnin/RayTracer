/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBox
*/

#pragma once

#include "Hittable.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include "Intersection.hpp"
#include "Sphere.hpp"
#include "Transformations.hpp"

namespace Raytracer {
    /**
     * @class SphereBox
     * @brief Class representing a box in 3D space.
     */
    class SphereBox : public Hittable {
    public:
        /**
         * @brief Construct a new SphereBox object with default parameters
         */
        SphereBox() {}

        /**
         * @brief Construct a new SphereBox object
         * 
         * @param center Center of the base of the box
         * @param radius Radius of the base of the box
         * @param height Height of the box
         * @param mat Material of the box
         */
        SphereBox(const Math::Point3D &center, double cubeSize,
                    double sphereRadius, shared_ptr<Material> mat);

        /**
         * @brief Determines if a ray hits the box
         * 
         * @param ray The ray to check
         * @param t The interval to check within
         * @param record The hit record to fill with hit information
         * @return true If the ray hits the box
         * @return false Otherwise
         */
        bool hit(const Ray &ray, Interval t, HitRecord &record) const override;

        /**
         * @brief Get the bounding box of the box
         * 
         * @return Intersection The bounding box
         */
        Intersection boundingBox() const override { return _bbox; }

    public:
        Math::Point3D _center; ///< Center of the base of the cube
        double _cubeSize; ///< Size of the cube
        double _sphereRadius; ///< Radius of the sphere
        shared_ptr<Material> _mat; ///< Material of the box
        Intersection _bbox; ///< Bounding box of the box
        shared_ptr<Hittable> _cube; ///< List of spheres forming the box
    };
}
