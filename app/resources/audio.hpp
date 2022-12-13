#pragma once

#include <common.hpp>
#include "utils.hpp"

#include <SFML/Audio.hpp>

namespace jumpr::resources
{

enum class [[nodiscard]] sound_id_t : u8 {
    BOUNCE, PROPELLER, BUTTON_PRESS, SELECTION_CHANGED, MAX};

enum class [[nodiscard]] track_id_t : u8 {TITLE, LEVEL, MAX};

struct track_t final
{
    // NOLINTNEXTLINE(readability-identifier-naming)
    [[nodiscard]] bool loadFromFile(std::string const& filename)
    {
        return source.openFromFile(filename);
    }

    sf::Music source {};
};

using Sounds = std::unordered_map<sound_id_t, std::unique_ptr<sf::SoundBuffer>>;
using Tracks = std::unordered_map<track_id_t, std::unique_ptr<track_t>>;

inline std::optional<Sounds> load_all_sounds(std::string const& directory)
{
    return load_all_resources<sound_id_t, sf::SoundBuffer>(directory);
}

inline std::optional<Tracks> load_all_music(std::string const& directory)
{
    return load_all_resources<track_id_t, track_t>(directory);
}

} // namespace jumpr::resources
