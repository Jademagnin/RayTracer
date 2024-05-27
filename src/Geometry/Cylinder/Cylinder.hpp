/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#pragma once

#include "Hittable.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

namespace Raytracer {
    /**
     * @class Cylinder
     * @brief Class representing a cylinder in 3D space.
     */
    class Cylinder : public Hittable {
    public:
        /**
         * @brief Construct a new Cylinder object
         * 
         * @param center Center of the base of the cylinder
         * @param radius Radius of the cylinder
         * @param height Height of the cylinder
         * @param mat Material of the cylinder
         */
        Cylinder(const Math::Point3D &center, double radius, double height, shared_ptr<Material> mat);

        /**
         * @brief Determines if a ray hits the cylinder
         * 
         * @param ray The ray to check
         * @param t The interval to check within
         * @param record The hit record to fill with hit information
         * @return true If the ray hits the cylinder
         * @return false Otherwise
         */
        bool hit(const Ray &ray, Interval t, HitRecord &record) const override;

        /**
         * @brief Get the bounding box of the cylinder
         * 
         * @return Intersection The bounding box
         */
        Intersection boundingBox() const override { return _bbox; }

    private:
        Math::Point3D _center; ///< Center of the base of the cylinder
        double _radius; ///< Radius of the cylinder
        double _height; ///< Height of the cylinder
        shared_ptr<Material> _mat; ///< Material of the cylinder
        Intersection _bbox; ///< Bounding box of the cylinder
    };
}
