/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material
*/

#pragma once

#include "IMaterial.hpp"

namespace Raytracer {
    class HitRecord;
    class Material : public IMaterial {
        public:
            bool scatter(const Ray &ray, const HitRecord &hit,
                Color &attenuation, Ray &scattered) const override;

        protected:
        private:
    };
}
