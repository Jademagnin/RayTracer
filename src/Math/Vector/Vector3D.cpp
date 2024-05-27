/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector
*/

#include "Vector3D.hpp"

namespace Math {
    // Constructors
    Vector3D::Vector3D(double x, double y, double z) : e{x, y, z} {}

    // Operators
    Vector3D &Vector3D::operator+=(const Vector3D &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vector3D &Vector3D::operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vector3D &Vector3D::operator/=(const double t)
    {
        return *this *= 1/t;
    }

    Vector3D &Vector3D::operator-=(const Vector3D &v)
    {
        return *this += -v;
    }

    double Vector3D::lengthSquared() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool Vector3D::nearZero() const {
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    // ostream
    std::ostream &operator<<(std::ostream &os, const Vector3D &v)
    {
        os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        return os;
    }
}
