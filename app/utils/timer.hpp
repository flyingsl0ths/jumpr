#pragma once

#include <chrono>

#include <common.hpp>

namespace utils
{

using clock_t = std::chrono::steady_clock;
using sec_t   = std::chrono::duration<f32>;

struct delta_time_t final
{
    sec_t operator++() noexcept
    {
        auto const now   = clock_t::now();
        auto const delta = now - point;
        point            = now;
        return delta;
    }

    clock_t::time_point point = clock_t::now();
};

} // namespace utils
