/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Interval
*/

#include "Interval.hpp"

namespace Raytracer {
    Interval::Interval() : min(+infinity), max(-infinity) {}

    Interval::Interval(double _min, double _max) : min(_min), max(_max) {}

    Interval::Interval(const Interval &a, const Interval &b)
    {
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    const Interval Interval::empty = Interval(+infinity, -infinity);
    const Interval Interval::universe = Interval(-infinity, +infinity);

    Interval operator+(const Interval &a, double displacement)
    {
        return Interval(a.min + displacement, a.max + displacement);
    }

    Interval operator+(double displacement, const Interval &a)
    {
        return a + displacement;
    }
}
