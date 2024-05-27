/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace Raytracer {
    Sphere::Sphere(const Math::Point3D &center, double radius,
        shared_ptr<Material> material)
        : _center1(center), _radius(fmax(0, radius)), _material(material), _is_moving(false)
    {
        auto rvec = Math::Vector3D(radius, radius, radius);
        _bbox = Intersection(_center1 - rvec, _center1 + rvec);
    }

    Sphere::Sphere(const Math::Point3D &center1, const Math::Vector3D &center2,
        double radius, shared_ptr<Material> material)
        : _center1(center1), _radius(fmax(0, radius)), _material(material), _is_moving(true)
    {
        auto rvec = Math::Vector3D(_radius, _radius, _radius);
        Intersection box1(_center1 - rvec, _center1 + rvec);
        Intersection box2(center2 - rvec, center2 + rvec);
        _bbox = Intersection(box1, box2);
        _center_vector = center2 - _center1;
    }

    bool Sphere::hit(const Raytracer::Ray& r, Interval interval, HitRecord& rec) const
    {
        Math::Vector3D center = _is_moving ? sphere_center(r.time()) : _center1;
        Math::Vector3D oc = center - r.origin();
        auto a = r.direction().lengthSquared();
        auto h = dot(r.direction(), oc);
        auto c = oc.lengthSquared() - _radius * _radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!interval.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!interval.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.point = r.pointAt(rec.t);
        Math::Vector3D outward_normal = (rec.point - center) / _radius;
        rec.setFaceNormal(r, outward_normal);
        get_sphere_uv(outward_normal, rec.u, rec.v);
        rec.material = _material;

        return true;
    }
}
