#pragma once

#include <chrono>

#include <common.hpp>

namespace utils
{

using clock_t = std::chrono::steady_clock;
using sec_t   = std::chrono::duration<f32>;

struct delta_time_t final
{
    void operator++() noexcept
    {
        auto const now = clock_t::now();
        tick           = now - point;
        point          = now;
    }

    clock_t::time_point point = clock_t::now();
    sec_t               tick {};
};

} // namespace utils
