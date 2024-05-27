/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Intersection
*/

#include "Intersection.hpp"

namespace Raytracer {
    Intersection::Intersection()
    {
    }

    Intersection::Intersection(const Interval &x, const Interval &y, const Interval &z)
        : x(x), y(y), z(z)
    {
        pad_to_min();
    }

    Intersection::Intersection(const Math::Point3D &a, const Math::Point3D &b)
    {
        x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
        y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
        z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);

        pad_to_min();
    }

    Intersection::Intersection(const Intersection &box0, const Intersection &box1)
    {
        x = Interval(box0.x, box1.x);
        y = Interval(box0.y, box1.y);
        z = Interval(box0.z, box1.z);
    }

    Intersection::~Intersection()
    {
    }

    const Interval& Intersection::axisInterval(int axis) const
    {
        return (axis == 1) ? y : (axis == 2) ? z : x;
    }

    bool Intersection::hit(const Ray &ray, Interval t) const
    {
        const Math::Point3D &origin = ray.origin();
        const Math::Vector3D &direction = ray.direction();

        for (int axis = 0; axis < 3; axis++) {
            const Interval &axisIn = axisInterval(axis);
            const double adinv = 1.0 / direction[axis];

            auto t0 = (axisIn.min - origin[axis]) * adinv;
            auto t1 = (axisIn.max - origin[axis]) * adinv;

            if (t0 < t1) {
                if (t0 > t.min)
                    t.min = t0;
                if (t1 < t.max)
                    t.max = t1;
            } else {
                if (t1 > t.min)
                    t.min = t1;
                if (t0 < t.max)
                    t.max = t0;
            }

            if (t.max <= t.min)
                return false;
        }
        return true;
    }

    int Intersection::longestAxis() const
    {
        if (x.size() > y.size())
            return x.size() > z.size() ? 0 : 2;
        else
            return y.size() > z.size() ? 1 : 2;
    }

    void Intersection::pad_to_min()
    {
        double delta = 0.0001;
        if (x.size() < delta)
            x = x.expand(delta);
        if (y.size() < delta)
            y = y.expand(delta);
        if (z.size() < delta)
            z = z.expand(delta);
    }

    const Intersection Intersection::empty    = Intersection(Interval::empty,    Interval::empty,    Interval::empty);
    const Intersection Intersection::universe = Intersection(Interval::universe, Interval::universe, Interval::universe);


    Intersection operator+(const Intersection &a, const Math::Vector3D &offset)
    {
        return Intersection(a.x + offset.x(), a.y + offset.y(), a.z + offset.z());
    }

    Intersection operator+(const Math::Vector3D &offset, const Intersection &a)
    {
        return a + offset;
    }
}
