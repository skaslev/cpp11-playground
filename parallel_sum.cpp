#include <future>
#include <vector>
#include <numeric>
#include <iostream>

template <class It>
auto parallel_sum(It beg, It end) -> typename It::value_type {
    using value_type = typename It::value_type;

    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, value_type(0));

    auto mid = beg + len / 2;
    auto handle = std::async([=]() { return parallel_sum(mid, end); });
    auto sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

int main() {
    std::vector<double> v(10000, 3.123456789);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << "\n";
    std::cout << "The sum is " << std::accumulate(v.begin(), v.end(), 0.0) << "\n";
}
