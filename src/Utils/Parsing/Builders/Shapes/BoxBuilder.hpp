/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** BoxBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class BoxBuilder : public Builder<Hittable> {
    public:
        BoxBuilder() = default;
        ~BoxBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
