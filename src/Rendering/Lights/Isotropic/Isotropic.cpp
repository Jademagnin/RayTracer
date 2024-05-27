/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Isotropic
*/

#include "Isotropic.hpp"

namespace Raytracer {
    Isotropic::Isotropic(const Color &color) : _tex(make_shared<Solid>(color)) {}

    Isotropic::Isotropic(shared_ptr<Texture> tex) : _tex(tex) {}

    bool Isotropic::scatter(const Ray &r_in, const HitRecord &rec,
        Color &attenuation, Ray &scattered) const
    {
        scattered = Ray(rec.point, Math::random_unit_vector(), r_in.time());
        attenuation = _tex->value(rec.u, rec.v, rec.point);
        return true;
    }
}
