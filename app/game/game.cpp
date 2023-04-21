#include "game.hpp"
#include "state.hpp"
#include "systems.hpp"

namespace jumpr::game
{

std::optional<str> app_t::load_resources(std::string const& root_dir)
{
    if (m_loaded_resources) { return "All resources have been loaded"; }

    m_loaded_resources = true;

    auto textures = resources::load_all_textures(root_dir + "data/textures");
    if (!textures) { return "Failed to load textures!\n"; }

    auto tracks = resources::load_all_music(root_dir + "data/audio/music");
    if (!tracks) { return "Failed to load music!\n"; }

    auto sounds = resources::load_all_sounds(root_dir + "data/audio/sounds");
    if (!sounds) { return "Failed to load sounds!\n"; }

    m_textures = std::move(*textures);
    m_sounds   = std::move(*sounds);
    m_tracks   = std::move(*tracks);

    return {};
}

void app_t::run()
{
    auto& window = m_window;

    m_timer     = {};
    auto& event = m_event;

    while (window.isOpen())
    {
        if (m_quit_game) { break; }

        ++m_timer;

        const auto [current, draw_previous] = systems::dispatch(m_state);

        auto const [setup, handle_input, update, draw] = current;

        if (m_state.just_entered_state)
        {
            setup(*this);
            m_state.just_entered_state = false;
        }

        event = {};

        while (window.pollEvent(event))
        {
            handle_input(*this);
            if (event.type == sf::Event::Closed) window.close();
        }

        update(*this);

        window.clear();

        draw(*this);

        if (draw_previous) { (*draw_previous)(*this); }

        window.display();

        if (m_state.next)
        {
            m_state.current = *m_state.next;
            m_state.next    = {};
        }
    }
}

} // namespace jumpr::game
