#pragma once

#include <type_traits>

#include <common.hpp>
#include <utils/vec2.hpp>

namespace jumpr::ecs::components
{

enum class component_id_t : u8
{
    PLAYER,
    JUMP_PAD,
    TRANSFORM,
    COLLIDER,
    ITEM,
    BUTTON
};

struct player_t final
{
    bool          is_jumping {};
    f32           points {};
    f32           air_time {};
    utils::vec2_t velocity {};
};

struct jump_pad_t final
{
    f32 traveled {};
    f32 max_distance {};
};

struct transform_t final
{
    f32           rotation {1.F};
    f32           scale {1.F};
    utils::vec2_t translation {};
};

struct collider_t final
{
    f32 top {};
    f32 left {};
    f32 right {};
    f32 bottom {};
};

struct item_t final
{
    f32 air_time {};
    // A variant of texture_id_t
    u8 image {};
};

template <typename T>
using callback_t = void (*)(T&);

template <typename T>
struct button_t final
{
    bool is_selected {};
    bool is_pressed {};
    // A variant of texture_id_t
    u8 default_img {};
    // A variant of texture_id_t
    u8 selected_img {};
    // A variant of texture_id_t
    u8            pressed_img {};
    callback_t<T> callback {};
};

template <typename T>
concept Component = std::is_aggregate_v<T> && std::is_final_v<T> &&
    std::is_default_constructible_v<T>;

template <Component C, typename T>
constexpr auto id_of() noexcept
{
    if constexpr (std::is_same_v<C, player_t>)
    {
        return component_id_t::PLAYER;
    }
    else if constexpr (std::is_same_v<C, jump_pad_t>)
    {
        return component_id_t::JUMP_PAD;
    }
    else if constexpr (std::is_same_v<C, transform_t>)
    {
        return component_id_t::TRANSFORM;
    }
    else if constexpr (std::is_same_v<C, collider_t>)
    {
        return component_id_t::COLLIDER;
    }
    else if constexpr (std::is_same_v<C, item_t>)
    {
        return component_id_t::ITEM;
    }
    else if constexpr (std::is_same_v<C, button_t<T>>)
    {
        return component_id_t::BUTTON;
    }
}

} // namespace jumpr::ecs::components
