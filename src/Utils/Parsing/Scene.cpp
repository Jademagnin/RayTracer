/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include <iostream>

Scene::Scene()
    : _shapeBuilders{
        {"sphere", std::make_shared<SphereBuilder>()},
        {"plane", std::make_shared<PlaneBuilder>()},
        {"cylinder", std::make_shared<CylinderBuilder>()},
        {"cone", std::make_shared<ConeBuilder>()},
        {"box", std::make_shared<BoxBuilder>()},
        {"spherebox", std::make_shared<SphereBoxBuilder>()},
    }
{
}

/*
    {
        ......

        transformations = {
            rotate = {
                angle = 90.0;
            };
            translate = {
                offset = {
                    x = 1.0;
                    y = 0.0;
                    z = 0.0;
                };
            };
        };
    }
*/

/*
    world.add(make_shared<Translation>(
        make_shared<Rotation>(
            make_shared<BVHNode>(boxes2), 15),
            Vector3D(-100,270,395)
        )
    );
*/

std::shared_ptr<Hittable> Scene::applyTransformations(
    std::shared_ptr<Hittable> shape, const libconfig::Setting &shapeSetting)
{
    if (!shapeSetting.exists("transformations") ||
        !shapeSetting["transformations"].getLength()) {
        return shape;
    }
    const libconfig::Setting &setting = shapeSetting["transformations"];

    Vector3D translation;
    double angle, densityAmount;

    if (setting.exists("translate")) {
        const libconfig::Setting &translationSetting = setting["translate"];
        translation = buildVector(translationSetting["offset"], {"x", "y", "z"});
        shape = std::make_shared<Translation>(shape, translation);
    }

    if (setting.exists("rotate")) {
        const libconfig::Setting &rotationSetting = setting["rotate"];
        angle = rotationSetting["angle"];
        shape = std::make_shared<Rotation>(shape, angle);
    }

    if (setting.exists("density")) {
        const libconfig::Setting &densitySetting = setting["density"];
        densityAmount = static_cast<double>(densitySetting["amount"]);
        auto densityTexture = _textureBuilder.build(densitySetting["texture"]);
        shape = std::make_shared<Density>(shape, densityAmount, densityTexture);
    }

    return shape;
}

Scene &Scene::addShape(const libconfig::Setting &shapeSetting,
    const Vector3D &origin)
{
    std::string type = S(shapeSetting, "type");
    auto builder = _shapeBuilders.find(type);
    if (builder == _shapeBuilders.end()) {
        throw UnknownShapeType(type);
    }
    std::shared_ptr<Hittable> shape = builder->second->build(shapeSetting);
    shape = applyTransformations(shape, shapeSetting);

    // Apply translation for the origin (for sub-scenes)
    shape = std::make_shared<Translation>(shape, origin);

    _world.add(shape);
    return *this;
}

Scene &Scene::addCamera(const libconfig::Setting &setting)
{
    // Set camera properties
    double aspect_ratio_numerator = SETTING("aspect_ratio_numerator");
    double aspect_ratio_denominator = SETTING("aspect_ratio_denominator");
    _camera.aspect_ratio = aspect_ratio_numerator / aspect_ratio_denominator;
    _camera.image_width = SETTING("image_width");
    _camera.samples_per_pixel = SETTING("samples_per_pixel");
    _camera.max_depth = SETTING("max_depth");
    _camera.background = buildVector(SETTING("background"), {"r", "g", "b"});

    _camera.vfov = SETTING("vfov");
    _camera.origin = buildVector(SETTING("origin"), {"x", "y", "z"});
    _camera.direction = buildVector(SETTING("direction"), {"x", "y", "z"});
    _camera.vup = buildVector(SETTING("vup"), {"x", "y", "z"});

    _camera.defocus_angle = SETTING("defocus_angle");
    return *this;
}
