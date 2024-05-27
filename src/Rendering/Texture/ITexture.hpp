/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ITexture
*/

#pragma once

#include "Color.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    class ITexture {
        public:
            virtual ~ITexture() = default;
            virtual Color value(double u, double v, const Math::Point3D &p) const = 0;

        protected:
        private:
    };
}
