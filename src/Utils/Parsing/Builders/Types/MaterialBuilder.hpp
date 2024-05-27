/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MaterialBuilder
*/

#pragma once

#include "TextureBuilder.hpp"

// Material
class MaterialBuilder : public Builder<Material> {
    public:
        class UnknownMaterialType : public std::exception {
            public:
                UnknownMaterialType(const std::string& type)
                    : message("Unknown material type: " + type) {}

                const char* what() const noexcept override {
                    return message.c_str();
                }

            private:
                std::string message;
        };

    public:
        MaterialBuilder();
        ~MaterialBuilder() = default;

        std::shared_ptr<Material> build(const libconfig::Setting& setting) override;

    private:
        TextureBuilder _textureBuilder;
        std::map<std::string, std::function<std::shared_ptr<Material>(const libconfig::Setting&)>> _materialBuilder;
};
