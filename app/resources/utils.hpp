#pragma once

#include <concepts>
#include <filesystem>
#include <memory>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include <common.hpp>

namespace fs = std::filesystem;

namespace jumpr::resources
{

template <typename T>
concept Enumerable = std::is_enum_v<T> &&
    std::is_unsigned_v<std::underlying_type_t<T>> && requires
{
    std::underlying_type_t<T> {} == std::underlying_type_t<T>(0);
    T {} < T::MAX;
};

template <Enumerable I, typename R>
requires requires
{
    {
        R {}.loadFromFile(std::string(""))
        } -> std::same_as<bool>;
}
std::optional<std::unordered_map<I, std::unique_ptr<R>>>
load_all_resources(str const directory)
{
    using resource_t = std::unique_ptr<R>;

    if (!fs::exists(directory)) { return {}; }

    const var resource_dir = fs::path(directory);

    std::underlying_type_t<I> resource_id {};

    std::unordered_map<I, resource_t> resources {};

    for (var const& resource : fs::directory_iterator(resource_dir))
    {
        if (static_cast<I>(resource_id) == I::MAX) { break; }

        var res = std::make_unique<R>();

        if (!res->loadFromFile(resource.path().string())) { return {}; }

        resources.insert(std::make_pair<I, resource_t>(
            static_cast<I>(resource_id++), std::move(res)));
    }

    return resources;
}

} // namespace jumpr::resources
