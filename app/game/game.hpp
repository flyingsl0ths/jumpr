#pragma once

#include <common.hpp>
#include <ecs/ecs.hpp>
#include <resources/audio.hpp>
#include <resources/textures.hpp>
#include <utils/timer.hpp>
#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace jumpr::game
{

struct app_t final
{
  public:
    friend std::optional<str> load_resources(app_t&             instance,
                                             std::string const& root_dir);

    friend void run(app_t& instance);

    [[nodiscard]] ecs::registry_t<app_t,
                                  ecs::components::player_t,
                                  ecs::components::jump_pad_t,
                                  ecs::components::transform_t,
                                  ecs::components::collider_t,
                                  ecs::components::item_t,
                                  ecs::components::button_t<app_t>>&
    registry() & noexcept
    {
        return m_entities;
    }

    [[nodiscard]] utils::sec_t dt() const& { return m_timer.tick; }

    [[nodiscard]] sf::Event get_event() & { return m_event; }

    void next_state(state::state_t const next) { m_states.next = next; }

    void top_back_states(state::state_t const top, state::state_t const back)
    {
        m_states.top_back(top, back);
    }

    void set_state(state::state_t const current) { m_states = current; }

    template <auto Id, typename R>
    requires((std::is_same_v<decltype(Id), resources::texture_id_t> &&
              std::is_same_v<R, sf::Texture>) ||
             (std::is_same_v<decltype(Id), resources::sound_id_t> &&
              std::is_same_v<R, sf::SoundBuffer>) ||
             (std::is_same_v<decltype(Id), resources::track_id_t> &&
              std::is_same_v<R, resources::track_t>))
        [[nodiscard]] std::optional<utils::non_owning_ptr_t<R>> get_resource()
    {
        if constexpr (std::is_same_v<decltype(Id), resources::texture_id_t>)
        {
            return !m_loaded_resources
                       ? std::optional<utils::non_owning_ptr_t<R>>()
                       : m_textures.at(Id).get();
        }

        else if constexpr (std::is_same_v<decltype(Id), resources::sound_id_t>)
        {
            return !m_loaded_resources
                       ? std::optional<utils::non_owning_ptr_t<R>>()
                       : m_sounds.at(Id).get();
        }
        else
        {
            return !m_loaded_resources
                       ? std::optional<utils::non_owning_ptr_t<R>>()
                       : m_tracks.at(Id).get();
        }
    }

  private:
    bool m_loaded_resources {};

    state::state_tracker_t m_states {};

    ecs::registry_t<app_t,
                    ecs::components::player_t,
                    ecs::components::jump_pad_t,
                    ecs::components::transform_t,
                    ecs::components::collider_t,
                    ecs::components::item_t,
                    ecs::components::button_t<app_t>>
        m_entities {};

    resources::Textures m_textures {};

    resources::Sounds m_sounds {};

    resources::Tracks m_tracks {};

    sf::RenderWindow m_window {sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                               "Jumpr",
                               sf::Style::Titlebar | sf::Style::Close};

    utils::delta_time_t m_timer {};

    sf::Event m_event {};
};

} // namespace jumpr::game
