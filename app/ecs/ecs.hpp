#pragma once

#include <optional>
#include <set>
#include <unordered_map>
#include <variant>
#include <vector>

#include <utils/non_owning_ptr.hpp>
#include "components.hpp"

namespace jumpr::ecs
{

using entity_t = u32;

template <typename T, components::Component... Cs>
struct registry_t final
{
  private:
    using entity_components_t =
        std::unordered_map<components::component_id_t, std::variant<Cs...>>;

  public:
    template <components::Component... C>
    [[maybe_unused]] std::optional<entity_t> create() &
    {
        const var unused = find_unused();

        const entity_t entity = unused ? *unused : m_ids++;

        // u32 Overflow handling
        if (m_entities.contains(entity)) { return {}; }

        if constexpr (sizeof...(C) > 0)
        {
            m_entities[entity] = {std::make_pair<components::component_id_t, C>(
                components::id_of<C, T>(), {C {}})...};
        }

        else
        {
            m_entities[entity] = {};
        }

        return entity;
    }

    void remove(const entity_t target) &
    {
        if (!m_entities.contains(target)) { return; }

        m_index.insert(target);
        m_entities.erase(target);
        --m_ids;
    }

    template <components::Component C>
    [[nodiscard]] std::optional<utils::non_owning_ptr_t<C>>
    get(const entity_t target) &
    {
        constexpr var COMPONENT_ID = components::id_of<C, T>();

        return !(m_entities.contains(target) &&
                 m_entities[target].contains(COMPONENT_ID))
                   ? std::optional<utils::non_owning_ptr_t<C>>()
                   : std::get_if<C>(&m_entities[target][COMPONENT_ID]);
    }

    template <components::Component... Ts>
    requires(sizeof...(Ts) > 1) void attach(const entity_t target) &
    {
        if (!m_entities.contains(target)) { return; }

        var& entity = m_entities[target];

        (entity.insert(std::make_pair<components::component_id_t, Ts>(
             components::id_of<Ts, T>(), {Ts {}})),
         ...);
    }

    template <components::Component C>
    utils::non_owning_ptr_t<C> attach(const entity_t target) &
    {
        if (!m_entities.contains(target)) { return; }

        var& entity = m_entities[target];

        auto [it, _] =
            entity.insert(std::make_pair<components::component_id_t, C>(
                components::id_of<C, T>(), {C {}}));

        return std::get_if<C>(&*it);
    }

    template <components::Component... Ts>
    bool dettach(const entity_t target) &
    {
        if (!m_entities.contains(target)) { return false; }

        (m_entities[target].erase(components::id_of<Ts, T>()), ...);
        return true;
    }

    template <components::Component C>
    std::vector<utils::non_owning_ptr_t<C>> all() &
    {
        std::vector<utils::non_owning_ptr_t<C>> acc {};
        constexpr var COMPONENT_ID = components::id_of<C, T>();
        for (var & [ entity, comps ] : m_entities)
        {
            if (comps.contains(COMPONENT_ID))
            {
                acc.push_back(std::get_if<C>(&comps[COMPONENT_ID]));
            }
        }
        return acc;
    }

    template <components::Component... Types,
              components::Component... Exclusions>
    std::vector<entity_t> query(Exclusions... /*unused*/) &
    {
        std::vector<std::reference_wrapper<std::variant<Types...>>> acc {};
        for (var & [ entity, comps ] : m_entities)
        {
            if ((... || !comps.contains(components::id_of<Exclusions, T>)) &&
                (... || comps.contains(components::id_of<Types, T>)))
            {
                acc.push_back(entity);
            }
        }
        return acc;
    }

  private:
    std::optional<entity_t> find_unused() &
    {
        if (m_index.empty()) { return {}; }

        var const entity = *m_index.begin();

        m_index.erase(entity);

        return entity;
    }

    u32                                               m_ids {};
    std::unordered_map<entity_t, entity_components_t> m_entities {};
    std::set<entity_t>                                m_index {};
};

} // namespace jumpr::ecs
