#include <iostream>
#include <tuple>
#include <type_traits>

template<size_t I>
using size_t_ = std::integral_constant<size_t, I>;

template<class... T, size_t I>
typename std::enable_if<I == sizeof...(T), void>::type
print_tuple(std::ostream& os, const std::tuple<T...>& t, size_t_<I>) {
  // nop
}

template<class... T, size_t I>
typename std::enable_if<I < sizeof...(T), void>::type
print_tuple(std::ostream& os, const std::tuple<T...>& t, size_t_<I>) {
  os << std::get<I>(t);
  if (I != sizeof...(T) - 1)
    os << ", ";
  print_tuple(os, t, size_t_<I + 1>());
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
