/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector3D
*/

#pragma once

#include "Vector3D.hpp"
#include "Constants.hpp"

namespace Math {
    class Vector3D {
        public:
            Vector3D() : e{0, 0, 0} {}
            Vector3D(double x, double y, double z);
            ~Vector3D() = default;

            Vector3D(const Vector3D &v) = default;
            Vector3D(Vector3D &&v) = default;
            Vector3D &operator=(const Vector3D &v) = default;
            Vector3D &operator=(Vector3D &&v) = default;

            Vector3D operator-() const { return Vector3D(-e[0], -e[1], -e[2]); }
            double operator[](int i) const { return e[i]; }
            double &operator[](int i) { return e[i]; }

            Vector3D &operator+=(const Vector3D &v);
            Vector3D &operator*=(const double t);
            Vector3D &operator/=(const double t);
            Vector3D &operator-=(const Vector3D &v);

        public:
            double x() const { return e[0]; }
            double y() const { return e[1]; }
            double z() const { return e[2]; }
            void setX(double x) { e[0] = x; }
            void setY(double y) { e[1] = y; }
            void setZ(double z) { e[2] = z; }
            double length() const { return sqrt(lengthSquared()); }
            double lengthSquared() const;
            bool nearZero() const;

            static Vector3D random()
            {
                return Vector3D(random_double(), random_double(), random_double());
            }

            static Vector3D random(double min, double max)
            {
                return Vector3D(random_double(min, max), random_double(min, max),
                    random_double(min, max));
            }

        public:
            double e[3];

        protected:
        private:
    };

    using Point3D = Vector3D;

    // ostream operator
    std::ostream &operator<<(std::ostream &os, const Vector3D &v);
    inline Vector3D operator+(const Vector3D &u, const Vector3D &v)
    {
        return Vector3D(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Vector3D operator-(const Vector3D &u, const Vector3D &v)
    {
        return Vector3D(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Vector3D operator*(const Vector3D &u, const Vector3D &v)
    {
        return Vector3D(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Vector3D operator*(double t, const Vector3D &v)
    {
        return Vector3D(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline Vector3D operator*(const Vector3D &v, double t)
    {
        return t * v;
    }

    inline Vector3D operator/(Vector3D v, double t)
    {
        return (1/t) * v;
    }

    inline double dot(const Vector3D &u, const Vector3D &v)
    {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline Vector3D cross(const Vector3D &u, const Vector3D &v)
    {
        return Vector3D(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                        u.e[2] * v.e[0] - u.e[0] * v.e[2],
                        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline Vector3D unit_vector(Vector3D v)
    {
        return v / v.length();
    }

    inline Vector3D random_in_unit_sphere()
    {
        while (true) {
            auto p = Vector3D::random(-1, 1);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    inline Vector3D random_unit_vector()
    {
        return unit_vector(Math::random_in_unit_sphere());
    }

    inline Vector3D random_on_hemisphere(const Vector3D &normal)
    {
        Vector3D in_unit_sphere = random_in_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0)
            return in_unit_sphere;
        return -in_unit_sphere;
    }

    inline Vector3D random_in_unit_disk()
    {
        while (true) {
            auto p = Vector3D(random_double(-1,1), random_double(-1,1), 0);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    inline Vector3D reflect(const Vector3D &v, const Vector3D &n)
    {
        return v - 2 * dot(v, n) * n;
    }


    inline Vector3D refract(const Vector3D& uv, const Vector3D& n,
        double etai_over_etat)
    {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        Vector3D r_out_perp =  etai_over_etat * (uv + cos_theta * n);
        Vector3D r_out_parallel = -sqrt(fabs(1.0
                                - r_out_perp.lengthSquared())) * n;
        return r_out_perp + r_out_parallel;
    }
} // namespace Math
