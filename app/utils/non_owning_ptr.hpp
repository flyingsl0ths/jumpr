#pragma once

namespace utils
{

template <typename T>
struct non_owning_ptr_t final
{
  public:
    non_owning_ptr_t(T* const value)
        : m_ptr {value}
    {
    }

    non_owning_ptr_t(non_owning_ptr_t const&) = delete;

    non_owning_ptr_t& operator=(non_owning_ptr_t const& other) = delete;

    non_owning_ptr_t(non_owning_ptr_t&& other) noexcept(true)
        : m_ptr {other.m_ptr}
    {
        other.m_ptr = nullptr;
    }

    non_owning_ptr_t& operator=(non_owning_ptr_t&& other) noexcept(true)
    {
        if (this == &other) { return *this; }
        m_ptr       = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    }

    ~non_owning_ptr_t() { m_ptr = nullptr; }

    T*               operator->() noexcept { return m_ptr; }
    [[nodiscard]] T& operator*() noexcept { return *m_ptr; }

  private:
    T* m_ptr;
};

template <typename T>
non_owning_ptr_t(T*) -> non_owning_ptr_t<T>;

} // namespace utils
