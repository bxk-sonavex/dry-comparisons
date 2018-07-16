#ifndef DRY_COMPARISONS_HPP_
#define DRY_COMPARISONS_HPP_

#include <utility>
#include <type_traits>
#include <tuple>
#include <functional>

namespace rollbear {

template <typename ... T>
class any_of : std::tuple<T...>
{
public:
    using std::tuple<T...>::tuple;
    template <typename U>
    constexpr auto operator==(const U& u) const
    -> decltype(((std::declval<const T&>() == u) || ...))
    {
        return std::apply([&](const auto& ... a) { return ((a == u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator==(const U& u, const any_of& a) -> decltype(a == u)
    {
        return a == u;
    }
    template <typename U>
    constexpr bool operator!=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a != u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator!=(const U& u, const any_of& a) -> decltype(a != u)
    {
        return a != u;
    }
    template <typename U>
    constexpr bool operator<(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a < u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator>(const U& u, const any_of& a) -> decltype(a < u)
    {
        return a < u;
    }
    template <typename U>
    constexpr bool operator<=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a <= u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator>=(const U& u, const any_of& a) -> decltype(a <= u)
    {
        return a <= u;
    }
    template <typename U>
    constexpr bool operator>(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a > u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator<(const U& u, const any_of& a) -> decltype(a > u)
    {
        return a > u;
    }
    template <typename U>
    constexpr bool operator>=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a >= u) || ...);},
                          get());
	
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, any_of>{}>>
    friend constexpr auto operator<=(const U& u, const any_of& a) -> decltype(a >= u)
    {
        return a >= u;
    }
private:
    constexpr const std::tuple<T...> get() const { return *this;}
};

template <typename ... T>
class none_of : std::tuple<T...>
{
public:
    using std::tuple<T...>::tuple;
    template <typename U>
    constexpr bool operator==(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a == u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator==(const U& u, const none_of& a) -> decltype(a == u)
    {
        return a == u;
    }
    template <typename U>
    constexpr bool operator!=(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a != u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator!=(const U& u, const none_of& a) -> decltype(a != u)
    {
        return a == u;
    }
    template <typename U>
    constexpr bool operator<(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a < u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator>(const U& u, const none_of& a) -> decltype(a < u)
    {
        return a < u;
    }
    template <typename U>
    constexpr bool operator<=(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a <= u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator>=(const U& u, const none_of& a) -> decltype(a <= u)
    {
        return a <= u;
    }
    template <typename U>
    constexpr bool operator>(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a > u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator<(const U& u, const none_of& a) -> decltype(a > u)
    {
        return a > u;
    }
    template <typename U>
    constexpr bool operator>=(const U& u) const {
        return std::apply([&](const auto& ... a) { return !((a >= u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, none_of>{}>>
    friend constexpr auto operator<=(const U& u, const none_of& a) -> decltype(a >= u)
    {
        return a >= u;
    }
private:
    constexpr const std::tuple<T...> get() const { return *this;}
};

template <typename ... T>
class all_of : std::tuple<T...>
{
public:
    using std::tuple<T...>::tuple;
    template <typename U>
    constexpr bool operator==(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a == u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator==(const U& u, const all_of& a) -> decltype(a == u)
    {
        return a == u;
    }
    template <typename U>
    constexpr bool operator!=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a != u) || ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator!=(const U& u, const all_of& a) -> decltype(a != u)
    {
        return a != u;
    }
    template <typename U>
    constexpr bool operator<(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a < u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator>(const U& u, const all_of& a) -> decltype(a < u)
    {
        return a < u;
    }
    template <typename U>
    constexpr bool operator<=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a <= u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator>=(const U& u, const all_of& a) -> decltype(a <= u)
    {
        return a <= u;
    }
    template <typename U>
    constexpr bool operator>(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a > u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator<(const U& u, const all_of& a) -> decltype(a > u)
    {
        return a > u;
    }
    template <typename U>
    constexpr bool operator>=(const U& u) const {
        return std::apply([&](const auto& ... a) { return ((a >= u) && ...);},
                          get());
    }
    template <typename U, typename = std::enable_if_t<!std::is_same<U, all_of>{}>>
    friend constexpr auto operator<=(const U& u, const all_of& a) -> decltype(a >= u)
    {
        return a >= u;
    }
private:
    constexpr const std::tuple<T...> get() const { return *this;}
};


template <typename ... T>
any_of(T&& ...) -> any_of<T...>;
template <typename ... T>
none_of(T&& ...) -> none_of<T...>;
template <typename ... T>
all_of(T&& ...) -> all_of<T...>;

}

#endif
