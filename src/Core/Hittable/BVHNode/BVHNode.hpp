/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** BVHNode
*/

#pragma once

#include "HittableList.hpp"
#include "Intersection.hpp"

#include <algorithm>

namespace Raytracer {
    class BVHNode : public Hittable {
        public:
            BVHNode(HittableList list);
            BVHNode(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end);
            ~BVHNode() {}

            bool hit(const Ray &ray, Interval t, HitRecord &rec) const override;

            Intersection boundingBox() const override { return _bbox; }

        public:
            static bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
                auto aInter = a->boundingBox().axisInterval(axis);
                auto bInter = b->boundingBox().axisInterval(axis);
                return aInter.min < bInter.min;
            }

            static bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
                return box_compare(a, b, 0);
            }

            static bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
                return box_compare(a, b, 1);
            }

            static bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
                return box_compare(a, b, 2);
            }

        protected:
        private:
            std::shared_ptr<Hittable> _left;
            std::shared_ptr<Hittable> _right;
            Intersection _bbox;
    };
}