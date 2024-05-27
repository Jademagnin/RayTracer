/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MaterialBuilder
*/

#include "MaterialBuilder.hpp"

// Material Builder
MaterialBuilder::MaterialBuilder()
    : _materialBuilder
    {
        ADD_BUILDER("lambertian", {
            if (setting.exists("albedo")) {
                return std::make_shared<Lambertian>(
                    buildVector(SETTING("albedo"), {"r", "g", "b"})
                );
            }
            if (setting.exists("texture")) {
                return std::make_shared<Lambertian>(
                    _textureBuilder.build(SETTING("texture"))
                );
            }
            throw MissingRequiredAttribute("albedo or texture");
        }),
        ADD_BUILDER("metal", {
            return std::make_shared<Metal>(Color(
                buildVector(SETTING("albedo"), {"r", "g", "b"})),
                SETTING("fuzz"));
        }),
        ADD_BUILDER("dielectric", {
            return std::make_shared<Dielectric>(SETTING("refraction_index"));
        }),
        ADD_BUILDER("diffuse", {
            if (setting.exists("texture")) {
                return std::make_shared<Diffuse>(
                    _textureBuilder.build(SETTING("texture"))
                );
            }
            if (setting.exists("color")) {
                return std::make_shared<Diffuse>(
                    buildVector(SETTING("color"), {"r", "g", "b"})
                );
            }
            throw MissingRequiredAttribute("color or texture");
        }),
        ADD_BUILDER("isotropic", {
            return std::make_shared<Isotropic>(
                _textureBuilder.build(SETTING("texture"))
            );
        }),
    }
{
}

std::shared_ptr<Material> MaterialBuilder::build(const libconfig::Setting& setting)
{
    if (!_materialBuilder.contains(SETTING("type"))) {
        throw UnknownMaterialType(SETTING("type"));
    }
    return _materialBuilder.at(SETTING("type"))(setting);
}
