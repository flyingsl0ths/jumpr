#pragma once

#include <common.hpp>

namespace utils
{

/// @brief A successful termination
constexpr s32 EX_OK = 0;

/// @brief Command line usage error
constexpr s32 EX_USAGE = 64;

/// @brief Unable to open input
constexpr s32 EX_NOINPUT = 66;

}; // namespace utils
