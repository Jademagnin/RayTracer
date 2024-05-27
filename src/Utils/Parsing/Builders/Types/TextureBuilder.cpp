/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** TextureBuilder
*/

#include "TextureBuilder.hpp"

TextureBuilder::TextureBuilder()
    : _textureBuilder
    {
        ADD_BUILDER("solid", {
            return std::make_shared<Solid>(
                buildVector(SETTING("color"), {"r", "g", "b"})
            );
        }),
        ADD_BUILDER("perlin", {
            return std::make_shared<Noise>(SETTING("scale"));
        }),
        ADD_BUILDER("image", {
            return std::make_shared<Image>(SETTING("path"));
        }),
        ADD_BUILDER("chessboard", {
            return std::make_shared<ChessBoard>(SETTING("scale"),
                build(SETTING("even")),
                build(SETTING("odd")));
        })
    }
{
}

std::shared_ptr<Texture> TextureBuilder::build(const libconfig::Setting& setting)
{
    // check if not in map
    if (!_textureBuilder.contains(SETTING("type"))) {
        throw UnknownTextureType(SETTING("type"));
    }
    return _textureBuilder.at(SETTING("type"))(setting);
}
