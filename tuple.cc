#include <tuple>
#include <type_traits>
#include <iostream>

//template<size_t I>
//using size_t_ = std::integral_constant<size_t, I>;
template<size_t I> struct size_t_ {};

template<class Tuple, size_t I>
void print_tuple(std::ostream& os, Tuple const& t, size_t_<I>) {
  print_tuple(os, t, size_t_<I-1>());
  os << ", " << std::get<I>(t);
}

template<class Tuple>
void print_tuple(std::ostream& os, const Tuple& t, size_t_<0>) {
  os << std::get<0>(t);
}

template<class ...T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& t) {
  os << "[";
  print_tuple(os, t, size_t_<sizeof...(T)-1>());
  return os << "]";
}

int main() {
  std::cout << std::make_tuple(3.14, 6.28f, "hey you") << "\n";
  return 0;
}
