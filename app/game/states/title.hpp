#pragma once

namespace jumpr::game
{
struct app_t;
} // namespace jumpr::game

namespace jumpr::game::title
{

void setup(app_t& app);

void handle_input(app_t&);

void update(app_t& app);

void draw(app_t& app);

} // namespace jumpr::game::title
