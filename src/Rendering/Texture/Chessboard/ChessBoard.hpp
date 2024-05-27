/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard
*/

#pragma once

#include "ATexture.hpp"
#include "Solid.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents a chessboard texture in the raytracer.
     */
    class ChessBoard : public Texture {
        public:
            /**
             * @brief Construct a new ChessBoard object with default scale and colors.
             */
            ChessBoard() = default;
            /**
             * @brief Construct a new ChessBoard object with a given scale and textures.
             * 
             * @param scale The scale of the chessboard.
             * @param even The texture for the even squares.
             * @param odd The texture for the odd squares.
             */
            ChessBoard(double scale, shared_ptr<Texture> even,
                        shared_ptr<Texture> odd);
            /**
             * @brief Construct a new ChessBoard object with a given scale and colors.
             * 
             * @param scale The scale of the chessboard.
             * @param c1 The color for the even squares.
             * @param c2 The color for the odd squares.
             */
            ChessBoard(double scale, const Color &c1, const Color &c2);
            /**
             * @brief Destroy the ChessBoard object.
             */
            ~ChessBoard() = default;

            ChessBoard(const ChessBoard &chessboard) = default;
            ChessBoard(ChessBoard &&chessboard) = default;
            ChessBoard &operator=(const ChessBoard &chessboard) = default;
            ChessBoard &operator=(ChessBoard &&chessboard) = default;

            /**
             * @brief Get the color of the chessboard at a given point.
             * 
             * @param u The u coordinate of the point.
             * @param v The v coordinate of the point.
             * @param p The 3D point.
             * @return Color The color of the chessboard at the point.
             */
            Color value(double u, double v, const Math::Point3D &p) const override;

        protected:
        private:
            double _inv_scale; ///< The inverse of the scale of the chessboard.
            shared_ptr<Texture> _even; ///< The texture for the even squares.
            shared_ptr<Texture> _odd; ///< The texture for the odd squares.
    };
} // namespace Raytracer