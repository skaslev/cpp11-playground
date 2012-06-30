#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m = {{42, 137}};

    for (auto x : {1, 2, 3, 4})
        m[x] = [](int x) { return x * x; }(x);

    for (auto it = m.cbegin(); it != m.cend(); ++it)
        std::cout << it->first  << ": " << it->second << "\n";

    return 0;
}
