/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBoxBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class SphereBoxBuilder : public Builder<Hittable> {
    public:
        SphereBoxBuilder() = default;
        ~SphereBoxBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
