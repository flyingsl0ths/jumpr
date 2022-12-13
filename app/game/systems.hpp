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
};

systems_t dispatch(const jumpr::game::state::state_tracker_t& state);

} // namespace jumpr::game::systems
