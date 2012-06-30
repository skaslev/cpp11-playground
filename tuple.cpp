#include <tuple>
#include <type_traits>
#include <iostream>

//template <size_t I>
//using size_t_ = std::integral_constant<size_t, I>;
template <size_t I> struct size_t_ {};

template <class Ch, class Traits, class Tuple, size_t I>
void print_tuple(std::basic_ostream<Ch, Traits>& os, Tuple const& t, size_t_<I>) {
    print_tuple(os, t, size_t_<I-1>());
    os << ", " << std::get<I>(t);
}

template <class Ch, class Traits, class Tuple>
void print_tuple(std::basic_ostream<Ch, Traits>& os, const Tuple& t, size_t_<0>) {
    os << std::get<0>(t);
}

namespace std {
    template <class Ch, class Traits, class... T>
    ostream& operator<<(basic_ostream<Ch, Traits>& os, const tuple<T...>& t) {
        os << "[";
        print_tuple(os, t, size_t_<sizeof...(T)-1>());
        return os << "]";
    }
}

int main() {
    std::cout << std::make_tuple(3.14, 6.28f, "hey you") << "\n";
    return 0;
}
