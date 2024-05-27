/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Translation
*/

#include "Translation.hpp"

namespace Raytracer
{
    Translation::Translation(std::shared_ptr<Hittable> object, const Math::Vector3D &offset)
        : _object(object), _offset(offset)
    {
        // bbox = object->boundingBox() + _offset;
    }

    bool Translation::hit(const Ray &ray, Interval t, HitRecord &rec) const
    {
        Ray _offsetRay(ray.origin() - _offset, ray.direction(), ray.time());

        if (!_object->hit(_offsetRay, t, rec))
            return false;

        rec.point += _offset;

        return true;
    }
}