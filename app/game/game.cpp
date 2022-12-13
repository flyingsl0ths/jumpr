#include "game.hpp"
#include "state.hpp"
#include "systems.hpp"

namespace jumpr::game
{

std::optional<str> load_resources(app_t& instance, std::string const& root_dir)
{
    if (instance.m_loaded_resources)
    {
        return "All resources have been loaded";
    }

    instance.m_loaded_resources = true;

    auto textures = resources::load_all_textures(root_dir + "data/textures");
    if (!textures) { return "Failed to load textures!\n"; }

    auto tracks = resources::load_all_music(root_dir + "data/audio/music");
    if (!tracks) { return "Failed to load music!\n"; }

    auto sounds = resources::load_all_sounds(root_dir + "data/audio/sounds");
    if (!sounds) { return "Failed to load sounds!\n"; }

    instance.m_textures = std::move(*textures);
    instance.m_sounds   = std::move(*sounds);
    instance.m_tracks   = std::move(*tracks);

    return {};
}

void run(app_t& instance)
{
    auto& window = instance.m_window;

    instance.m_timer = {};
    auto& event      = instance.m_event;

    while (window.isOpen())
    {
        ++instance.m_timer;

        auto const [current, draw_previous] =
            systems::dispatch(instance.m_states);

        auto const [setup, handle_input, update, draw] = current;

        if (instance.m_states.just_entered_state)
        {
            setup(instance);
            instance.m_states.just_entered_state = false;
        }

        event = {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            handle_input(instance);
        }

        update(instance);

        window.clear();

        draw(instance);

        if (draw_previous) { (*draw_previous)(instance); }

        window.display();

        if (instance.m_states.next)
        {
            instance.m_states.current = *instance.m_states.next;
            instance.m_states.next    = {};
        }
    }
}

} // namespace jumpr::game
