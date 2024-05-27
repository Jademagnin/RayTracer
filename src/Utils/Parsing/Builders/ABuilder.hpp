/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ABuilder
*/

#pragma once

#include "IBuilder.hpp"

// Macros
#define SETTING(name) getSetting(setting, name)
#define S(setting, name) getSetting(setting, name)
#define ADD_BUILDER(type, body) {type, [this]( \
    const libconfig::Setting& setting) body }

// Functions
template<typename... Args>
const libconfig::Setting& getSetting(const libconfig::Setting& parent,
    const std::string& first, Args... rest);

const libconfig::Setting& getSetting(const libconfig::Setting& parent,
    const std::string& name);

const Vector3D buildVector(const libconfig::Setting& setting,
    const std::vector<std::string>& keys);

double getScale(const libconfig::Setting &setting);

// Exceptions
class MissingRequiredAttribute : public std::exception {
    public:
        MissingRequiredAttribute(const std::string& attribute)
            : message("Missing required attribute: " + attribute) {}

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

class InvalidParameter : public std::exception {
    public:
        InvalidParameter(const std::string& parameter)
            : message("Invalid parameter: " + parameter) {}

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

template <typename T>
class Builder : public IBuilder<T> {
    // Builder
    public:
        virtual ~Builder() = default;

    protected:
    private:
};
