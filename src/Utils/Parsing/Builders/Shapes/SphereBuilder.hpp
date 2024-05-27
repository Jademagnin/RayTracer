/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class SphereBuilder : public Builder<Hittable> {
    public:
        SphereBuilder() = default;
        ~SphereBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
