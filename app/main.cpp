#include <iostream>
#include <span>

#include "common.hpp"
#include "game/game.hpp"
#include "utils/exit_codes.hpp"

s32 main(const s32 argc, const char** const argv)
{
    using namespace jumpr;

    if (argc != 2)
    {
        std::cerr << "Failed to specify root directory for all resources!\n";
        return utils::EX_USAGE;
    }

    auto const args     = std::span(argv, argc);
    auto const root_dir = std::string(args.back()) + "/";

    game::app_t instance {};

    auto error_message = load_resources(instance, root_dir);
    if (error_message)
    {
        std::cerr << *error_message;
        return utils::EX_NOINPUT;
    }

    run(instance);

    return utils::EX_OK;
}
