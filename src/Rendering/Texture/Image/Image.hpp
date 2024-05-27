/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image
*/

#pragma once

#include "ATexture.hpp"
#include "Solid.hpp"
#include "img_manager.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents an image texture in the raytracer.
     */
    class Image : public Texture {
        public:
            /**
             * @brief Construct a new Image object with default path.
             */
            Image() = default;
            /**
             * @brief Construct a new Image object with a given path.
             * 
             * @param path The path to the image file.
             */
            Image(const std::string &path) : image(path) {}
            /**
             * @brief Destroy the Image object.
             */
            ~Image() = default;

            Image(const Image &image) = default;
            Image(Image &&image) = default;
            Image &operator=(const Image &image) = default;
            Image &operator=(Image &&image) = default;

            /**
             * @brief Get the color of the image at a given point.
             * 
             * @param u The u coordinate of the point.
             * @param v The v coordinate of the point.
             * @param p The 3D point.
             * @return Color The color of the image at the point.
             */
            Color value(double u, double v, const Math::Point3D &p) const override;

        public:
            ImgManager image; ///< The image manager that handles the image file.
        protected:
        private:
    };
} // namespace Raytracer
