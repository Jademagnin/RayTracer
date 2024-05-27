/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

namespace Raytracer {
    void HitRecord::setFaceNormal(const Ray &r, const Math::Vector3D &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
}
