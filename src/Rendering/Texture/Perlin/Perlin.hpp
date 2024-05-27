/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Perlin
*/

#pragma once

#include "Vector3D.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a Perlin noise generator.
     */
    class Perlin {
    public:
        /**
         * @brief Construct a new Perlin object.
         */
        Perlin();
        /**
         * @brief Destroy the Perlin object.
         */
        ~Perlin();

        /**
         * @brief Generate Perlin noise for a given point.
         * 
         * @param p The point for which to generate Perlin noise.
         * @return double The generated Perlin noise.
         */
        double noise(const Math::Point3D &p) const;
        /**
         * @brief Generate Perlin turbulence for a given point.
         * 
         * @param p The point for which to generate Perlin turbulence.
         * @param depth The depth of the turbulence.
         * @return double The generated Perlin turbulence.
         */
        double turbulence(const Math::Vector3D &p, int depth) const;

    protected:

    private:
        static int *perlin_generate_perm();
        static void permute(int *p, int n);
        static double perlin_interp(const Math::Vector3D c[2][2][2], double u, double v, double w);

    private:
        static const int point_count = 256; ///< The number of points for which to generate Perlin noise.
        Math::Vector3D *randvec; ///< The random vector used in the Perlin noise generation.
        int *perm_x; ///< The permutation for the x coordinate.
        int *perm_y; ///< The permutation for the y coordinate.
        int *perm_z; ///< The permutation for the z coordinate.
    };
}
