/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** img_manager
*/

#include "img_manager.hpp"

sf::Image ImgManager::loadImage(const std::string &path)
{
    sf::Image image;
    std::vector<std::string> probablePaths = {
        path,
        "assets/" + path,
        "assets/textures/" + path,
        "assets/images/" + path,
        "images/" + path,
        "textures/" + path,
    };

    for (const auto &probablePath : probablePaths) {
        if (std::filesystem::exists(probablePath)
            && image.loadFromFile(probablePath)) {
            _image = image;
            return _image;
        }
    }

    throw ImgManagerException("Failed to load image: " + path);
}
