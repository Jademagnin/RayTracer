/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HittableList
*/

#include "HittableList.hpp"

namespace Raytracer {
    bool HittableList::hit(const Ray &ray, Interval interval,
        HitRecord &record) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = interval.max;

        for (const auto &object : objects) {
            if (object->hit(ray, Interval(interval.min, closest_so_far),
                temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                record = temp_rec;
            }
        }
        return hit_anything;
    }

    void HittableList::add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
        _bbox = Intersection(_bbox, object->boundingBox());
    }
}
