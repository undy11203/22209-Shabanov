#pragma once

template <typename Ch, typename Tr, std::size_t N, typename... Args>
void Print(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &t) {
    if constexpr (N < sizeof...(Args)) {
        os << std::get<N>(t) << (N < sizeof...(Args) - 1 ? ", " : "");
        Print<Ch, Tr, N + 1, Args...>(os, t);
    }
}

template <typename Ch, typename Tr, typename... Args>
auto &operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &t) {
    os << "{ ";
    Print<Ch, Tr, 0, Args...>(os, t);
    os << " }";
    return os;
}