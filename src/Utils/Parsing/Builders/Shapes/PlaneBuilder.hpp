/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlaneBuilder
*/

#pragma once

#include "ABuilder.hpp"
#include "MaterialBuilder.hpp"

class PlaneBuilder : public Builder<Hittable> {
    public:
        PlaneBuilder() = default;
        ~PlaneBuilder() = default;

        std::shared_ptr<Hittable> build(const libconfig::Setting &setting) override;

    protected:
    private:
        MaterialBuilder _materialBuilder;
};
