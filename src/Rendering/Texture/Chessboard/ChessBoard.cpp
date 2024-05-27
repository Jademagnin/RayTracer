/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard
*/

#include "ChessBoard.hpp"

namespace Raytracer {
    ChessBoard::ChessBoard(double scale, shared_ptr<Texture> even,
        shared_ptr<Texture> odd) : _inv_scale(1.0 / scale),
                                    _even(even), _odd(odd)
    {
    }

    ChessBoard::ChessBoard(double scale,
        const Color &c1, const Color &c2) : _inv_scale(1.0 / scale),
                                            _even(make_shared<Solid>(c1)),
                                            _odd(make_shared<Solid>(c2))
    {
    }

    Color ChessBoard::value(double u, double v, const Math::Point3D &p) const
    {
        auto xInt = int(std::floor(_inv_scale * p.x()));
        auto yInt = int(std::floor(_inv_scale * p.y()));
        auto zInt = int(std::floor(_inv_scale * p.z()));

        bool isEven = !((xInt + yInt + zInt) % 2);

        return isEven ? _even->value(u, v, p) : _odd->value(u, v, p);
    }
}
