/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Hittable
*/

#pragma once

#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Interval.hpp"
#include "Intersection.hpp"

namespace Raytracer {
    class Hittable {
        public:
            virtual ~Hittable() = default;

        public:
            virtual bool hit(const Raytracer::Ray &ray, Interval interval,
                HitRecord &record) const = 0;
            virtual Intersection boundingBox() const = 0;

        protected:
        private:
    };
}
