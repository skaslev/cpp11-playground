#include <iostream>
#include <functional>
#include <unordered_map>

//template <size_t I>
//using size_t_ = std::integral_constant<size_t, I>;
template <size_t I> struct size_t_ {};

template <class T>
size_t hash_combine(size_t hash, const T& v) {
    std::hash<T> hasher;
    return hash ^ (hasher(v) + 0x9e3779b9 + (hash << 6) + (hash >> 2));
}

template <class... T, size_t I>
size_t hash_tuple(size_t hash, const std::tuple<T...>& t, size_t_<I>) {
    return hash_tuple(hash_combine(hash, std::get<I>(t)), t, size_t_<I-1>());
}

template <class... T>
size_t hash_tuple(size_t hash, const std::tuple<T...>& t, size_t_<0>) {
    return hash_combine(hash, std::get<0>(t));
}

namespace std {
    template <class... T>
    struct hash<tuple<T...>> {
        size_t operator()(const tuple<T...>& t) const {
            return hash_tuple(0, t, size_t_<sizeof...(T)-1>());
        }
    };
}

template <class Res, class... Args>
auto memo(std::function<Res(Args...)> f) -> std::function<Res(Args...)> {
    std::unordered_map<std::tuple<Args...>, Res> cache;
    return [&](Args... args) {
        auto t = std::make_tuple(args...);
        auto it = cache.find(t);
        if (it != cache.end())
            return it->second;

        Res res = f(args...);
        cache[t] = res;
        return res;
    };
}

int main() {
    const int N = 42;

    std::function<double(int)> fib = [&](int n) -> double {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        return fib(n-1) + fib(n-2);
    };
    fib = memo(fib);

    std::cout << fib(N) << "\n";

    return 0;
}
