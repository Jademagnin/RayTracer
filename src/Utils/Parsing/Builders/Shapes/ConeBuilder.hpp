/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ConeBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class ConeBuilder : public Builder<Hittable> {
    public:
        ConeBuilder() = default;
        ~ConeBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
