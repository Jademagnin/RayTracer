/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBox
*/

#include "SphereBox.hpp"

namespace Raytracer {
    using namespace Math;

    SphereBox::SphereBox(const Point3D &center, double cudeSize,
        double sphereRadius, shared_ptr<Material> mat)
        : _center(center), _cubeSize(cudeSize), _sphereRadius(sphereRadius), _mat(mat)
    {
        _bbox = Intersection(
            center - Point3D(cudeSize, cudeSize, cudeSize),
            center + Point3D(cudeSize, cudeSize, cudeSize)
        );

        // Calculate the number of spheres based on the cube size
        int ns = static_cast<int>(_cubeSize * 7); // don't ask why 7

        HittableList rawCube;
        for (int i = 0; i < ns; i++) {
            rawCube.add(make_shared<Sphere>(Point3D::random(0, _cubeSize),
                _sphereRadius, _mat));
        }

        _cube = make_shared<Translation>(
            make_shared<BVHNode>(rawCube),
            _center
        );
    }

    bool SphereBox::hit(const Ray &ray, Interval t, HitRecord &record) const {
        return _cube->hit(ray, t, record);
    }
}
