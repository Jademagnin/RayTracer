/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CylinderBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class CylinderBuilder : public Builder<Hittable> {
    public:
        CylinderBuilder() = default;
        ~CylinderBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
