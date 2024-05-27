/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ABuilder
*/

#include "ABuilder.hpp"

// Base case for recursion
const libconfig::Setting& getSetting(const libconfig::Setting& parent,
    const std::string& name)
{
    try {
        return parent[name.c_str()];
    } catch (const libconfig::SettingNotFoundException& e) {
        throw MissingRequiredAttribute(name);
    }
}

// Recursive template function
template<typename... Args>
const libconfig::Setting& getSetting(const libconfig::Setting& parent,
    const std::string& first, Args... rest)
{
    const libconfig::Setting& nextParent = getSetting(parent, first);
    return getSetting(nextParent, rest...);
}

const Vector3D buildVector(const libconfig::Setting& setting,
    const std::vector<std::string>& keys)
{
    if (keys.size() != 3) {
        throw InvalidParameter("Keys should have a size of 3 (found "
            + std::to_string(keys.size()) + ")");
    }
    return Vector3D(
        getSetting(setting, keys[0]),
        getSetting(setting, keys[1]),
        getSetting(setting, keys[2])
    );
}

double getScale(const libconfig::Setting &setting)
{
    double scale;
    try {
        scale = SETTING("scale");
    } catch (const MissingRequiredAttribute &e) {
        scale = 1;
    }
    return scale;
}
