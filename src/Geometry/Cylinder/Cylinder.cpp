/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace Raytracer {
    Cylinder::Cylinder(const Math::Point3D &center, double radius, double height, shared_ptr<Material> mat)
        : _center(center), _radius(radius), _height(height), _mat(mat) {
        Math::Vector3D rvec(radius, height / 2, radius);
        _bbox = Intersection(_center - rvec, _center + rvec);
    }

    bool Cylinder::hit(const Ray &ray, Interval t, HitRecord &record) const {
        // Check if the ray intersects the bounding box.
        if (!_bbox.hit(ray, t))
            return false;

        // Calculate the intersections with the cylinder.
        Math::Vector3D oc = ray.origin() - _center;
        double a = ray.direction().x() * ray.direction().x() + ray.direction().z() * ray.direction().z();
        double half_b = oc.x() * ray.direction().x() + oc.z() * ray.direction().z();
        double c = oc.x() * oc.x() + oc.z() * oc.z() - _radius * _radius;
        double discriminant = half_b * half_b - a * c;

        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (root < t.min || t.max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t.min || t.max < root)
                return false;
        }

        // Check if the intersection point is within the height of the cylinder.
        double y = ray.origin().y() + root * ray.direction().y();
        if (y < _center.y() - _height / 2 || y > _center.y() + _height / 2) {
            // If the intersection point is not within the height of the cylinder,
            // check for intersections with the top and bottom caps.
            double t0 = (_center.y() - _height / 2 - ray.origin().y()) / ray.direction().y();
            double t1 = (_center.y() + _height / 2 - ray.origin().y()) / ray.direction().y();
            if (t0 > t.min && t0 < t.max) {
                double x = ray.origin().x() + t0 * ray.direction().x();
                double z = ray.origin().z() + t0 * ray.direction().z();
                if ((x - _center.x()) * (x - _center.x()) + (z - _center.z()) * (z - _center.z()) <= _radius * _radius) {
                    record.t = t0;
                    record.point = ray.pointAt(record.t);
                    record.setFaceNormal(ray, Math::Vector3D(0, -1, 0));
                    record.material = _mat;
                    return true;
                }
            }
            if (t1 > t.min && t1 < t.max) {
                double x = ray.origin().x() + t1 * ray.direction().x();
                double z = ray.origin().z() + t1 * ray.direction().z();
                if ((x - _center.x()) * (x - _center.x()) + (z - _center.z()) * (z - _center.z()) <= _radius * _radius) {
                    record.t = t1;
                    record.point = ray.pointAt(record.t);
                    record.setFaceNormal(ray, Math::Vector3D(0, 1, 0));
                    record.material = _mat;
                    return true;
                }
            }
            return false;
        }

        record.t = root;
        record.point = ray.pointAt(record.t);
        Math::Vector3D outward_normal = (record.point - _center);
        outward_normal.setY(0);
        outward_normal = outward_normal / outward_normal.length();

        // Adjust the normal vector based on the direction of the ray.
        if (dot(ray.direction(), outward_normal) > 0)
            outward_normal = -outward_normal;

        record.setFaceNormal(ray, outward_normal);
        record.material = _mat;

        return true;
    }
}
