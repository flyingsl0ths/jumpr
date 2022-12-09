#pragma once

#include <cstdint>
#include <string_view>

#define var auto
#define typeof decltype

using u8  = unsigned char;
using u32 = std::uint32_t;
using usz = std::size_t;
using s32 = std::int32_t;
using f32 = float;
using f64 = double;
using szt = std::size_t;
using str = std::string_view;

constexpr u32 WINDOW_WIDTH {1280U};
constexpr u32 WINDOW_HEIGHT {720U};
