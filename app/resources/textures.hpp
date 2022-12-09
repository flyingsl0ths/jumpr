#pragma once

#include <common.hpp>
#include "utils.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace jumpr::resources
{

enum class [[nodiscard]] texture_id_t : u8 {BUTTON,
                                            BUTTON_SELECTED,
                                            BUTTON_PRESSED,
                                            PLAYER,
                                            ENEMY,
                                            ENEMY2,
                                            SPRING,
                                            SPRING2,
                                            PROPELLER,
                                            MAX};

using Textures = std::unordered_map<texture_id_t, std::unique_ptr<sf::Texture>>;

inline std::optional<Textures> load_all_textures(str const directory)
{
    return load_all_resources<texture_id_t, sf::Texture>(directory);
}

} // namespace jumpr::resources
