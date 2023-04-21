#include "systems.hpp"
#include <common.hpp>
#include "state.hpp"
#include "states/level.hpp"
#include "states/pause.hpp"
#include "states/title.hpp"

constexpr std::array<jumpr::game::systems::system_t, 4UL> TITLE = {
    jumpr::game::title::setup,
    jumpr::game::title::handle_input,
    jumpr::game::title::update,
    jumpr::game::title::draw};

constexpr std::array<jumpr::game::systems::system_t, 4UL> LEVEL = {
    jumpr::game::level::setup,
    jumpr::game::level::handle_input,
    jumpr::game::level::update,
    jumpr::game::level::draw};

constexpr std::array<jumpr::game::systems::system_t, 4UL> PAUSE = {
    jumpr::game::pause::setup,
    jumpr::game::pause::handle_input,
    jumpr::game::pause::update,
    jumpr::game::pause::draw};

namespace jumpr::game::systems
{

systems_t dispatch(jumpr::game::state::state_tracker_t const& state)
{
    auto const current = state.current;

    if (state.previous && *state.previous == state::state_t::LEVEL &&
        current == state::state_t::PAUSED)
    {
        return {.current = PAUSE, .draw_previous = LEVEL[3UL]};
    }

    switch (current)
    {
        case state::state_t::TITLE: return {TITLE};
        default: return {LEVEL};
    }
}

} // namespace jumpr::game::systems
