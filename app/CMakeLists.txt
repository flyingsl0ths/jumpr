add_executable(${PROJECT_NAME} main.cpp)

list(APPEND ECS "ecs/ecs.hpp" "ecs/components.hpp")

list(APPEND RESOURCES "resources/utils.hpp" "resources/textures.hpp"
     "resources/audio.hpp")

list(APPEND UTILS "utils/exit_codes.hpp" "utils/non_owning_ptr.hpp"
     "utils/timer.hpp" "utils/vec2.hpp" "common.hpp")

list(
  APPEND
  GAME
  "game/game.hpp"
  "game/game.cpp"
  "game/state.hpp"
  "game/systems.hpp"
  "game/systems.cpp"
  "game/states/title.hpp"
  "game/states/title.cpp"
  "game/states/level.hpp"
  "game/states/level.cpp"
  "game/states/pause.hpp"
  "game/states/pause.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${ECS} ${RESOURCES} ${UTILS} ${GAME})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/app")

target_link_libraries(${PROJECT_NAME} PRIVATE compile-options sfml-graphics
                                              sfml-window sfml-system sfml-audio)
