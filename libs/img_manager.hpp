/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** img_manager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

class ImgManager {
    public:
        ImgManager() = default;
        ImgManager(const std::string &path) { loadImage(path); }
        ~ImgManager() = default;

        ImgManager(const ImgManager &imgManager) = default;
        ImgManager(ImgManager &&imgManager) = default;
        ImgManager &operator=(const ImgManager &imgManager) = default;
        ImgManager &operator=(ImgManager &&imgManager) = default;

        sf::Image loadImage(const std::string &path);
        sf::Image loadImage(const sf::Image &image) { _image = image; return _image; }
        sf::Image getImage() const { return _image; }

        int width() const { return _image.getSize().x; }
        int height() const { return _image.getSize().y; }
        sf::Vector2u getSize() const { return _image.getSize(); }

        sf::Color getPixel(int x, int y) const { return _image.getPixel(x, y); }
        void setPixelData(int x, int y, sf::Color color) { _image.setPixel(x, y, color); }
    public:
        class ImgManagerException : public std::exception {
            public:
                ImgManagerException(const std::string &message) : _message(message) {}
                const char *what() const noexcept override { return _message.c_str(); }
            private:
                std::string _message;
        };

    protected:
    private:
        sf::Image _image;
};
