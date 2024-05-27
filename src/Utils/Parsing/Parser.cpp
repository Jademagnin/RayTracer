/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Parser
*/

#include "Parser.hpp"

void Parser::parseFile(const std::string &path, bool sub_scene,
    const Vector3D &origin)
{
    libconfig::Config config;

    try {
        config.readFile(path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw ReadError(path);
    } catch (const libconfig::ParseException &pex) {
        throw ParseError(std::string("Parse error at ") + pex.getFile() + ":" +
            std::to_string(pex.getLine()) + " - " + pex.getError());
    }

    if (!sub_scene) {
        const libconfig::Setting& camera_cfg = config.lookup("camera");
        _scene.addCamera(camera_cfg);
    }

    const libconfig::Setting& scene_cfg = config.lookup("scene");
    for (int i = 0; i < scene_cfg.getLength(); i++) {
        _scene.addShape(scene_cfg[i], origin);
    }

    parseSubScenes(config.getRoot());
}

void Parser::parseSubScenes(const libconfig::Setting &parentConfig)
{
    if (!parentConfig.exists("sub_scenes")) {
        return;
    }
    const libconfig::Setting& sub_scenes_cfg = parentConfig.lookup("sub_scenes");
    int length = sub_scenes_cfg.getLength();
    std::clog << "Context from " << length << " sub-scenes" << std::endl;
    for (int i = 0; i < length; i++) {
        Vector3D sub_scene_origin;
        if (sub_scenes_cfg[i].exists("translate")) {
            const libconfig::Setting& sub_scene = sub_scenes_cfg[i];
            sub_scene_origin = buildVector(
                S(sub_scene, "translate"), {"x", "y", "z"}
            );
        }
        parseFile(S(sub_scenes_cfg[i], "path"), true, sub_scene_origin);
    }
}
