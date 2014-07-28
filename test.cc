#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, int> m = {{42, 137}};

  for (auto&& x : {1, 2, 3, 4})
    m[x] = [](int x) { return x * x; }(x);

  for (auto&& x : m)
    std::cout << x.first  << ": " << x.second << "\n";

  return 0;
}
