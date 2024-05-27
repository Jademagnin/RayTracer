/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Density
*/

#include "Density.hpp"

namespace Raytracer
{
    Density::Density(shared_ptr<Hittable> boundary, double density, shared_ptr<Texture> tex)
        : _boundary(boundary), _density(-1/density), _phaseFunction(make_shared<Isotropic>(tex))
    {
    }

    Density::Density(shared_ptr<Hittable> boundary, double density, const Color &color)
        : _boundary(boundary), _density(-1/density), _phaseFunction(make_shared<Isotropic>(color))
    {
    }

    bool Density::hit(const Ray &ray, Interval t, HitRecord &rec) const
    {
        const bool enableDebug = false;
        const bool debug = enableDebug && random_double() < 0.00001;

        HitRecord rec1, rec2;

        if (!_boundary->hit(ray, Interval::universe, rec1))
            return false;

        if (!_boundary->hit(ray, Interval(rec1.t + 0.0001, infinity), rec2))
            return false;

        if (debug) std::clog << "\nt0 t1 " << rec1.t << " " << rec2.t << "\n";

        if (rec1.t < t.min)
            rec1.t = t.min;

        if (rec2.t > t.max)
            rec2.t = t.max;

        if (rec1.t >= rec2.t)
            return false;

        if (rec1.t < 0)
            rec1.t = 0;

        auto ray_length = ray.direction().length();
        auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
        auto hit_distance = _density * log(random_double());

        if (hit_distance > distance_inside_boundary)
            return false;

        rec.t = rec1.t + hit_distance / ray_length;
        rec.point = ray.pointAt(rec.t);

        if (debug) std::clog << "hit_distance = " << hit_distance << "\n"
                             << "rec.t = " << rec.t << "\n"
                             << "rec.point = " << rec.point << "\n";

        rec.normal = Math::Vector3D(1, 0, 0); // arbitrary
        rec.front_face = true; // arbitrary
        rec.material = _phaseFunction;

        return true;

    }

}
