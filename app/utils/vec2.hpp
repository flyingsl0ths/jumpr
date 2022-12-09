#pragma once

#include <cmath>

#include "common.hpp"

namespace utils
{

struct vec2_t final
{
    [[nodiscard]] constexpr auto
    operator<=>(vec2_t const& other) const noexcept = default;

    [[nodiscard]] constexpr vec2_t operator+(vec2_t const& other) const noexcept
    {
        return vec2_t {x + other.x, y + other.y};
    }

    [[maybe_unused]] vec2_t& operator+=(vec2_t const& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] constexpr vec2_t operator-(vec2_t const& other) const noexcept
    {
        return vec2_t {x - other.x, y - other.y};
    }

    [[maybe_unused]] vec2_t& operator-=(const vec2_t other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    [[nodiscard]] constexpr vec2_t operator*(const f32 scalar) const noexcept
    {
        return vec2_t {x * scalar, y * scalar};
    }

    [[maybe_unused]] vec2_t& operator*=(const f32 scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    [[nodiscard]] constexpr f32 len() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] constexpr f32 dot(vec2_t const& other) const noexcept
    {
        return (x * other.x) + (y * other.y);
    }

    [[nodiscard]] constexpr f32 angle_to(vec2_t const& other) const
    {
        return std::atan2(other.y - y, other.x - x);
    }

    f32 x {};
    f32 y {};
};

} // namespace utils
