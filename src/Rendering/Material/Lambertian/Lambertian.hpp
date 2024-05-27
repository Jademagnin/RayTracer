/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Ambiant
*/

#pragma once

#include "AMaterial.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"
#include "Texture.hpp"

namespace Raytracer {
    class HitRecord;
    /**
     * @brief A class that represents a Lambertian material in the raytracer.
     */
    class Lambertian : public Material {
        public:
            /**
             * @brief Construct a new Lambertian object with default albedo.
             */
            Lambertian() = default;
            /**
             * @brief Construct a new Lambertian object with a given albedo.
             * 
             * @param albedo The albedo of the Lambertian material.
             */
            Lambertian(const Color &albedo) : _texture(make_shared<Solid>(albedo)) {}
            /**
             * @brief Construct a new Lambertian object with a given texture.
             * 
             * @param texture The texture of the Lambertian material.
             */
            Lambertian(shared_ptr<Texture> texture) : _texture(texture) {}
            /**
             * @brief Destroy the Lambertian object.
             */
            ~Lambertian() = default;

            Lambertian(const Lambertian &lambertian) = default;
            Lambertian(Lambertian &&lambertian) = default;
            Lambertian &operator=(const Lambertian &lambertian) = default;
            Lambertian &operator=(Lambertian &&lambertian) = default;

            /**
             * @brief Set the Texture object.
             * 
             * @param texture The new texture.
             */
            void setTexture(shared_ptr<Texture> texture) { _texture = texture; }
            /**
             * @brief Get the Texture object.
             * 
             * @return Texture* The current texture.
             */
            Texture *getTexture() const { return _texture.get(); }

            /**
             * @brief Scatter a ray off the Lambertian material.
             * 
             * @param ray The incident ray.
             * @param hit The hit record of the ray with the material.
             * @param attenuation The attenuation of the scattered ray.
             * @param scattered The scattered ray.
             * @return true If the ray was scattered.
             * @return false Otherwise.
             */
            bool scatter(const Ray &ray, const HitRecord &hit,
                Color &attenuation, Ray &scattered) const override;

        public:

        private:
            shared_ptr<Texture> _texture; ///< The texture of the Lambertian material.

        protected:
        private:
    };
} // namespace Raytracer