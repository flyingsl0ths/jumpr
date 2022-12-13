#pragma once

#include <array>
#include <optional>

namespace jumpr::game
{

struct app_t;

namespace state
{
struct state_tracker_t;
}
} // namespace jumpr::game

namespace jumpr::game::systems
{

using system_t = void (*)(jumpr::game::app_t&);

struct systems_t final
{
    std::array<system_t, 4UL> current {};
    std::optional<system_t>   draw_previous {};
};

systems_t dispatch(jumpr::game::state::state_tracker_t const& state);

} // namespace jumpr::game::systems
