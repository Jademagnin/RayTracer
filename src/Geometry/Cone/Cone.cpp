/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#include "Cone.hpp"

namespace Raytracer {
    using namespace Math;

    Cone::Cone(const Point3D &center, double radius, double height, shared_ptr<Material> mat)
        : _center(center), _radius(radius), _height(height), _mat(mat) {
        Vector3D rvec(radius, height, radius);
        _bbox = Intersection(_center - rvec, _center + rvec);
    }

    bool Cone::hit(const Ray &ray, Interval t, HitRecord &record) const {
        // Check if the ray intersects the bounding box.
        if (!_bbox.hit(ray, t)) {
            return false;
        }

        Vector3D oc = ray.origin() - _center;
        double k = _radius / _height;
        double k2 = k * k;
        double a = ray.direction().x() * ray.direction().x() + ray.direction().z() * ray.direction().z() - k2 * ray.direction().y() * ray.direction().y();
        double b = 2 * (oc.x() * ray.direction().x() + oc.z() * ray.direction().z() - k2 * oc.y() * ray.direction().y());
        double c = oc.x() * oc.x() + oc.z() * oc.z() - k2 * oc.y() * oc.y();

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-b - sqrtd) / (2.0 * a);
        if (root < t.min || t.max < root) {
            root = (-b + sqrtd) / (2.0 * a);
            if (root < t.min || t.max < root)
                return false;
        }

        // Check if the intersection point is within the height of the cone.
        double y = ray.origin().y() + root * ray.direction().y();
        if (y > _center.y() || y < _center.y() - _height) {
            return false;
        }

        record.t = root;
        record.point = ray.pointAt(record.t);
        Vector3D outward_normal = (record.point - _center);
        outward_normal.setY(outward_normal.y() * k);
        outward_normal = outward_normal / outward_normal.length();
        if (dot(ray.direction(), outward_normal) > 0) {
            outward_normal = -outward_normal;
        }
        record.setFaceNormal(ray, outward_normal);
        record.material = _mat;

        return true;
    }
}
