/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

namespace Raytracer {
    Plane::Plane(const Math::Point3D &Q, const Math::Vector3D &u, const Math::Vector3D &v, shared_ptr<Material> mat)
        : _Q(Q), _u(u), _v(v), _mat(mat)
    {
        auto n = cross(_u, _v);
        _normal = unit_vector(n);
        _d = dot(_normal, _Q);
        _w = n / dot(n, n);

        set_bounding_box();
    }

    void Plane::set_bounding_box()
    {
        auto box1 = Intersection(_Q, _Q + _u + _v);
        auto box2 = Intersection(_Q, _Q + _u - _v);
        _bbox = Intersection(box1, box2);
    }

    bool Plane::hit(const Ray &ray, Interval t, HitRecord &record) const
    {
        auto denom = dot(_normal, ray.direction());

        if (fabs(denom) < 1e-8)
            return false;

        auto t0 = (_d - dot(_normal, ray.origin())) / denom;
        if (!t.contains(t0))
            return false;

        auto intersection_point = ray.pointAt(t0);

        Math::Vector3D pVector = intersection_point - _Q;
        auto alpha = dot(_w, cross(pVector, _v));
        auto beta = dot(_w, cross(_u, pVector));

        if (!is_interior(alpha, beta, record))
            return false;

        record.t = t0;
        record.point = intersection_point;
        record.material = _mat;
        record.setFaceNormal(ray, _normal);

        return true;
    }

    bool Plane::is_interior(double alpha, double beta, HitRecord &record) const
    {
        Interval unit_interval(0, 1);

        if (!unit_interval.contains(alpha) || !unit_interval.contains(beta))
            return false;

        record.u = alpha;
        record.v = beta;

        return true;
    }
}