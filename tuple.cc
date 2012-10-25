#include <tuple>
#include <type_traits>
#include <iostream>

//template<size_t S>
//using size_t_ = std::integral_constant<size_t, S>;
template<size_t S> struct size_t_ {};

template<class... T, size_t S>
typename std::enable_if<S < sizeof...(T), void>::type
print_tuple(std::ostream& os, const std::tuple<T...>& t, size_t_<S>) {
  os << std::get<S>(t);
  if (S != sizeof...(T) - 1)
    os << ", ";
  print_tuple(os, t, size_t_<S + 1>());
}

template<class... T, size_t S>
typename std::enable_if<S == sizeof...(T), void>::type
print_tuple(std::ostream& os, const std::tuple<T...>& t, size_t_<S>) {
  // nop
}

template<class... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& t) {
  os << "[";
  print_tuple(os, t, size_t_<0>());
  return os << "]";
}

int main() {
  std::cout << std::make_tuple() << "\n";
  std::cout << std::make_tuple(42) << "\n";
  std::cout << std::make_tuple(3.14, 6.28f, "hey you") << "\n";
  return 0;
}
