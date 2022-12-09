#pragma once

#include <optional>

#include <common.hpp>

namespace jumpr::game::state
{

enum class [[nodiscard]] state_t : u8 {TITLE, LEVEL, PAUSED};

struct state_tracker_t final
{
    state_tracker_t& operator=(state_t const new_state) & noexcept
    {
        if (previous) { previous = {}; }
        current = new_state;
        return *this;
    }

    void top_back(state_t const top, state_t const back) & noexcept
    {
        current  = top;
        previous = back;
    }

    bool                   just_entered_state {};
    bool                   is_paused {};
    state_t                current {state_t::TITLE};
    std::optional<state_t> next {};
    std::optional<state_t> previous {};
};

} // namespace jumpr::game::state
