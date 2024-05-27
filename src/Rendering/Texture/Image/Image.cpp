/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image
*/

#include "Image.hpp"

namespace Raytracer {
    Color Image::value(double u, double v, const Math::Point3D &p) const
    {
        (void)p;

        if (image.height() <= 0) return Color(0, 1, 1);

        u = Interval(0,1).clamp(u);
        v = 1.0 - Interval(0,1).clamp(v);

        auto i = static_cast<int>(u * image.width());
        auto j = static_cast<int>(v * image.height());
        auto pixel = image.getPixel(i, j);

        auto scale = 1.0 / 255.0;
        return Color(scale * pixel.r, scale * pixel.g, scale * pixel.b);
    }
} // namespace Raytracer
