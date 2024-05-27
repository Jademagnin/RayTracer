/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Interval
*/

#pragma once

#include "Constants.hpp"

namespace Raytracer {
    /**
     * @brief A class that represents an interval on the real number line.
     */
    class Interval {
        public:
            Interval();
            Interval(double min, double max);
            Interval(const Interval &a, const Interval &b);
            ~Interval() = default;

            Interval(const Interval &interval) = default;
            Interval(Interval &&interval) = default;
            Interval &operator=(const Interval &interval) = default;
            Interval &operator=(Interval &&interval) = default;

        public:
            /**
             * @brief Get the size of the interval.
             * 
             * @return double The size of the interval.
             */
            double size() const { return max - min; }

            /**
             * @brief Check if a number is contained in the interval.
             * 
             * @param x The number to check.
             * @return bool True if the number is in the interval, false otherwise.
             */
            bool contains(double x) const {
                return x >= min && x <= max;
            }

            /**
             * @brief Check if a number is surrounded by the interval.
             * 
             * @param x The number to check.
             * @return bool True if the number is surrounded by the interval, false otherwise.
             */
            bool surrounds(double x) const {
                return x > min && x < max;
            }

            /**
             * @brief Clamp a number to the interval.
             * 
             * @param x The number to clamp.
             * @return double The clamped number.
             */
            double clamp(double x) const {
                if (x < min) return min;
                if (x > max) return max;
                return x;
            }

            /**
             * @brief Expand the interval by a certain amount.
             * 
             * @param delta The amount to expand the interval by.
             * @return Interval The expanded interval.
             */
            Interval expand(double delta) const {
                auto padding = delta / 2;
                return Interval(min - padding, max + padding);
            }

        public:
            double min, max; ///< The minimum and maximum values of the interval.
            static const Interval empty, universe; ///< Static instances representing an empty interval and the entire real number line.

        protected:
        private:
    };

    /**
     * @brief Add a displacement to an interval.
     * 
     * @param a The interval.
     * @param displacement The displacement.
     * @return Interval The displaced interval.
     */
    Interval operator+(const Interval &a, double displacement);

    /**
     * @brief Add a displacement to an interval.
     * 
     * @param displacement The displacement.
     * @param a The interval.
     * @return Interval The displaced interval.
     */
    Interval operator+(double displacement, const Interval &a);
} // namespace Raytracer
