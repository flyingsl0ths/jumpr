#pragma once

#include <ecs/ecs.hpp>
#include <resources/audio.hpp>
#include <resources/textures.hpp>
#include <utils/timer.hpp>
#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace jumpr::game
{

struct app_t final
{
    state::state_tracker_t states {};

    ecs::registry_t<app_t,
                    components::player_t,
                    components::jump_pad_t,
                    components::transform_t,
                    components::collider_t,
                    components::item_t,
                    components::button_t<app_t>>
        entities {};

    std::unordered_map<resources::texture_id_t, sf::Texture> textures {};

    std::unordered_map<resources::sound_id_t, sf::Sound> sounds {};

    sf::RenderWindow canvas {sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                             "Jumpr",
                             sf::Style::Titlebar | sf::Style::Close};

    utils::delta_time_t timer {};
};

} // namespace jumpr::game