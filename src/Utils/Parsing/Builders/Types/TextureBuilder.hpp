/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** TextureBuilder
*/

#pragma once

#include "ABuilder.hpp"

class TextureBuilder : public Builder<Texture> {
    public:
        class UnknownTextureType : public std::exception {
            public:
                UnknownTextureType(const std::string& type)
                    : message("Unknown texture type: " + type) {}

                const char* what() const noexcept override {
                    return message.c_str();
                }

            private:
                std::string message;
        };

    public:
        TextureBuilder();
        ~TextureBuilder() = default;

        std::shared_ptr<Texture> build(const libconfig::Setting& setting) override;

    protected:
    private:
        std::map<std::string, std::function<std::shared_ptr<Texture>(const libconfig::Setting&)>> _textureBuilder;
};
