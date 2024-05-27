/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#include "Color.hpp"

namespace Raytracer {
    inline double linear_to_gamma(double x)
    {
        return x > 0 ? sqrt(x) : 0;
    }

    void write_color(std::ostream &out, const Color &pixel_color)
    {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        // Translate the [0,1] color to [0,255]
        static const Interval intensity(0.000, 0.999);
        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));

        // Write out the pixel color
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
}
