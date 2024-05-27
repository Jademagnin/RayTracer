/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#pragma once

#include "Hittable.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

namespace Raytracer {
    /**
     * @class Cone
     * @brief Class representing a cone in 3D space.
     */
    class Cone : public Hittable {
    public:
        /**
         * @brief Construct a new Cone object with default parameters
         */
        Cone() {}

        /**
         * @brief Construct a new Cone object
         * 
         * @param center Center of the base of the cone
         * @param radius Radius of the base of the cone
         * @param height Height of the cone
         * @param mat Material of the cone
         */
        Cone(const Math::Point3D &center, double radius, double height, shared_ptr<Material> mat);

        /**
         * @brief Determines if a ray hits the cone
         * 
         * @param ray The ray to check
         * @param t The interval to check within
         * @param record The hit record to fill with hit information
         * @return true If the ray hits the cone
         * @return false Otherwise
         */
        bool hit(const Ray &ray, Interval t, HitRecord &record) const override;

        /**
         * @brief Get the bounding box of the cone
         * 
         * @return Intersection The bounding box
         */
        Intersection boundingBox() const override { return _bbox; }

    public:
        Math::Point3D _center; ///< Center of the base of the cone
        double _radius; ///< Radius of the base of the cone
        double _height; ///< Height of the cone
        shared_ptr<Material> _mat; ///< Material of the cone
        Intersection _bbox; ///< Bounding box of the cone
    };
}
