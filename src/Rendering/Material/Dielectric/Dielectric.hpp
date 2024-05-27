/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Ambiant
*/

#pragma once

#include "AMaterial.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"

namespace Raytracer {
    class HitRecord;

    class Dielectric : public Material {
        public:
            Dielectric() = default;
            Dielectric(double refraction_index) : refraction_index(refraction_index) {}
            ~Dielectric() = default;

            Dielectric(const Dielectric &Dielectric) = default;
            Dielectric(Dielectric &&Dielectric) = default;
            Dielectric &operator=(const Dielectric &Dielectric) = default;
            Dielectric &operator=(Dielectric &&Dielectric) = default;

            bool scatter(const Ray &ray, const HitRecord &hit,
                Color &attenuation, Ray &scattered) const override;

        public:

        private:
            static double reflectance(double cosine, double ref_idx) {
                auto r0 = (1 - ref_idx) / (1 + ref_idx);
                r0 = r0 * r0;
                return r0 + (1 - r0) * pow((1 - cosine), 5);
            }

        private:
            double refraction_index;
    };
}
