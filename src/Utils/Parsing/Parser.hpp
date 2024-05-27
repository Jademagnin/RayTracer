/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Parser
*/

#pragma once

#include "Raytracer.hpp"
#include "Scene.hpp"

#include <libconfig.h++>
#include <iostream>

using namespace Raytracer;
using namespace Math;

// Exceptions
class ParseError : public std::exception {
    public:
        ParseError(const std::string &message) : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};

class ReadError : public ParseError {
    public:
        ReadError(const std::string &path) : ParseError("Cannot read file: " + path) {}
};

class Parser {
    public:
        Parser() = default;
        Parser(const std::string &path) { parseFile(path); }
        ~Parser() = default;

        Parser(const Parser &parser) = default;
        Parser(Parser &&parser) = default;
        Parser &operator=(const Parser &parser) = default;
        Parser &operator=(Parser &&parser) = default;

        void parseFile(const std::string &path, bool sub_scene = false,
            const Vector3D &origin = Vector3D(0, 0, 0));
        Scene &getScene() { return _scene; }
        void render() { _scene.render(); }

    protected:
    private:
        void parseSubScenes(const libconfig::Setting &sub_scenes_cfg);
        Scene _scene;
};
