/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#pragma once

#include "Camera.hpp"
#include "Core.hpp"
#include "Transformations.hpp"
#include "Builders.hpp"

#include <libconfig.h++>

using namespace Raytracer;

/**
 * @brief Exception thrown when an unknown shape type is encountered.
 */
class UnknownShapeType : public std::exception {
    public:
        /**
         * @brief Construct a new UnknownShapeType object.
         * 
         * @param type The unknown shape type.
         */
        UnknownShapeType(const std::string& type)
            : message("Unknown shape type: " + type) {}

        /**
         * @brief Get the error message.
         * 
         * @return const char* The error message.
         */
        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message; ///< The error message.
};

/**
 * @brief A class that represents a scene to be rendered.
 */
class Scene {
    public:
        Scene();
        ~Scene() = default;

        /**
         * @brief Add a shape to the scene.
         * 
         * @param shapeSetting The settings for the shape.
         * @return Scene& A reference to the scene.
         */
        Scene& addShape(const libconfig::Setting &shapeSetting,
            const Vector3D &origin = Vector3D(0, 0, 0));

        /**
         * @brief Add a camera to the scene.
         * 
         * @param cameraSetting The settings for the camera.
         * @return Scene& A reference to the scene.
         */
        Scene& addCamera(const libconfig::Setting& cameraSetting);
        std::shared_ptr<Hittable> applyTransformations(
            std::shared_ptr<Hittable> shape,
            const libconfig::Setting& shapeSetting
        );

        /**
         * @brief Render the scene.
         */
        void render() { _camera.render(_world); }

    protected:
    private:
        Camera _camera; ///< The camera for the scene.
        HittableList _world; ///< The list of hittable objects in the scene.
        std::map<std::string,
        std::shared_ptr<Builder<Hittable>>> _shapeBuilders; ///< The builders for the shapes in the scene.
        TextureBuilder _textureBuilder; ///< The builders for the texture in the scene.
};