/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#pragma once

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Intersection.hpp"
#include "Hittable.hpp"

namespace Raytracer {
    /**
     * @class Plane
     * @brief Class representing a plane in 3D space.
     */
    class Plane : public Hittable {
    public:
        /**
         * @brief Construct a new Plane object
         * 
         * @param Q Point on the plane
         * @param u Direction vector along the plane
         * @param v Direction vector along the plane
         * @param mat Material of the plane
         */
        Plane(const Math::Point3D &Q, const Math::Vector3D &u, const Math::Vector3D &v, shared_ptr<Material> mat);

        /**
         * @brief Set the bounding box of the plane
         */
        virtual void set_bounding_box();

        /**
         * @brief Check if a point defined by alpha and beta is inside the plane
         * 
         * @param alpha Coordinate along the u direction
         * @param beta Coordinate along the v direction
         * @param record The hit record to fill with hit information
         * @return true If the point is inside the plane
         * @return false Otherwise
         */
        virtual bool is_interior(double alpha, double beta, HitRecord &record) const;

        /**
         * @brief Get the bounding box of the plane
         * 
         * @return Intersection The bounding box
         */
        Intersection boundingBox() const override { return _bbox; }

        /**
         * @brief Determines if a ray hits the plane
         * 
         * @param ray The ray to check
         * @param t The interval to check within
         * @param record The hit record to fill with hit information
         * @return true If the ray hits the plane
         * @return false Otherwise
         */
        bool hit(const Ray &ray, Interval t, HitRecord &record) const override;

    private:
        Math::Point3D _Q; ///< Point on the plane
        Math::Vector3D _u; ///< Direction vector along the plane
        Math::Vector3D _v; ///< Direction vector along the plane
        Math::Vector3D _w; ///< Direction vector perpendicular to the plane
        shared_ptr<Material> _mat; ///< Material of the plane
        Intersection _bbox; ///< Bounding box of the plane
        Math::Vector3D _normal; ///< Normal vector of the plane
        double _d; ///< Distance from the origin to the plane along the normal
    };
}
