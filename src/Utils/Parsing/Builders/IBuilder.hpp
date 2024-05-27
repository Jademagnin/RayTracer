/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IBuilder
*/

#pragma once

#include "Hittable.hpp"
#include "Geometry.hpp"
#include "Math.hpp"
#include "Lights.hpp"

#include <libconfig.h++>
#include <memory>

using namespace Math;
using namespace Raytracer;

template <typename T>
class IBuilder {
    public:
        virtual ~IBuilder() = default;
        virtual std::shared_ptr<T> build(const libconfig::Setting &setting) = 0;

    protected:
    private:
};
