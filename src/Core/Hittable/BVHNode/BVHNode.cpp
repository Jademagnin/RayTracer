/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** BVHNode
*/

#include "BVHNode.hpp"

namespace Raytracer {
    BVHNode::BVHNode(HittableList list): BVHNode(list.objects, 0, list.objects.size()) {}

    BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end)
    {
        _bbox = Intersection::empty;
        for (size_t obj_id = start; obj_id < end; obj_id++)
            _bbox = Intersection(_bbox, objects[obj_id]->boundingBox());

        int axis = _bbox.longestAxis();

        auto comparator = (axis == 0) ? box_x_compare
                        : (axis == 1) ? box_y_compare
                                      : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            _left = _right = objects[start];
        } else if (object_span == 2) {
                _left = objects[start];
                _right = objects[start + 1];
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
            _left = std::make_shared<BVHNode>(objects, start, mid);
            _right = std::make_shared<BVHNode>(objects, mid, end);
        }

        // _bbox = Intersection(_left->boundingBox(), _right->boundingBox());
    }

    bool BVHNode::hit(const Ray &ray, Interval t, HitRecord &record) const
    {
        if (!_bbox.hit(ray, t))
            return false;

        bool hit_left = _left->hit(ray, t, record);
        bool hit_right = _right->hit(ray, Interval(t.min, hit_left ? record.t : t.max), record);
        return hit_left || hit_right;
    };
}
