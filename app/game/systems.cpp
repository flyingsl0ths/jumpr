#include "systems.hpp"
#include <common.hpp>
#include <game/state.hpp>
#include "states/level.hpp"
#include "states/pause.hpp"
#include "states/title.hpp"

constexpr std::array<jumpr::game::systems::system_t, 3UL> TITLE = {
    jumpr::game::title::setup,
    jumpr::game::title::update,
    jumpr::game::title::draw};

constexpr std::array<jumpr::game::systems::system_t, 3UL> LEVEL = {
    jumpr::game::level::setup,
    jumpr::game::level::update,
    jumpr::game::level::draw};

constexpr std::array<jumpr::game::systems::system_t, 3UL> PAUSE = {
    jumpr::game::pause::setup,
    jumpr::game::pause::update,
    jumpr::game::pause::draw};

namespace jumpr::game::systems
{

systems_t dispatch(jumpr::game::state::state_tracker_t const& state)
{
    var const current = state.current;

    if (state.previous && *state.previous == state::state_t::LEVEL &&
        current == state::state_t::PAUSED)
    {
        return {.current = PAUSE, .previous = {LEVEL}};
    }

    switch (current)
    {
        case state::state_t::TITLE: return {TITLE};
        default: return {LEVEL};
    }
}

} // namespace jumpr::game::systems
