#include <shared/all_stl.h>

template <typename Num, typename... Nums> consteval Num Product(Num num, Nums... nums) {
    if constexpr (sizeof...(nums) > 0)
        return num * Product(nums...);
    return num;
}
template <typename Num, size_t Cnt> consteval Num ProductV2(Num (&&nums)[Cnt]) {
    Num ret = 1;
    for (auto num : nums)
        ret *= num;
    return ret;
}
template <typename... Nums> consteval auto ProductV3(Nums... nums) { return (... * nums); }

template <size_t I, typename Tup> void printTuple(const Tup &tuple) {
    if constexpr (I == std::tuple_size_v<Tup>)
        return;
    else {
        std::cout << '[' << std::get<I>(tuple) << ']';
        printTuple<I + 1>(tuple);
    }
}
template <typename T> constexpr bool AlwaysFalse = false;
template <typename Tup> void PrintTuple(const Tup &tuple) {
    if constexpr (std::tuple_size_v<Tup> == 0)
        // static_assert(false, "Not a valid tuple type.");
        static_assert(AlwaysFalse<Tup>, "Not a valid tuple type.");

    printTuple<0>(tuple);
    std::cout << '\n';
}

template <typename Tup> void PrintTupleV2(const Tup &tuple) {
    if constexpr (std::tuple_size_v<Tup> == 0)
        // static_assert(false, "Not a valid tuple type.");
        static_assert(AlwaysFalse<Tup>, "Not a valid tuple type.");

    [&]<size_t... Is>(std::index_sequence<Is...>) {
        ((std::cout << '[' << std::get<Is>(tuple) << ']'), ...);
    }(std::make_index_sequence<std::tuple_size_v<Tup>>{});

    std::cout << '\n';
}

template <typename T, size_t N> void PrintArray(const std::array<T, N> &arr) {
    for (auto &e : arr)
        std::cout << '[' << e << ']';
    std::cout << '\n';
}

template <typename T> constexpr T &&TypeForward(std::remove_reference_t<T> &x) {
    return static_cast<T &&>(x);
}
template <typename T> constexpr T &&TypeForward(std::remove_reference_t<T> &&x) {
    return static_cast<T &&>(x);
}
template <typename T> void WrongCastFromUniRef(T &&ref) { std::remove_reference_t<T> a = ref; }
template <typename T> void CorrectCastFromUniRef(T &&ref) {
    std::remove_reference_t<T> a = TypeForward<T>(ref);
}

template <size_t N> struct StringLiteral {
    char data[N];

    constexpr StringLiteral(const char (&str)[N]) { std::copy_n(str, N, data); }
};

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Universal Reference", []() {
            struct A {
                A() = default;
                A(const A &) { PRINT_FUNC; }
                A(A &&) noexcept { PRINT_FUNC; }
            };
            A a;
            WrongCastFromUniRef(a);
            CorrectCastFromUniRef(a);
            WrongCastFromUniRef(std::move(a));
            CorrectCastFromUniRef(std::move(a));
        });
        testFuncs.emplace("Constexpr Product", []() {
            auto prod = Product(1, 2, 3, 4);
            std::cout << prod << '\n';

            prod = ProductV2({1, 2, 3, 4});
            std::cout << prod << '\n';

            prod = ProductV3(1, 2, 3, 4);
            std::cout << prod << '\n';
        });
        testFuncs.emplace("Tuple Print", []() {
            std::tuple<int, char, double> tup = {1, 'x', 2.3333};
            PrintTuple(tup);
            PrintTupleV2(tup);
        });
        testFuncs.emplace("Array", []() {
            std::array chs = {'a', 'b', 'c'};
            // std::array chs = {'a', 'b', 0};
            std::array strs = {"abs", "123", "\0"};
            // std::array strs = {"abs", "123", nullptr};
            PrintArray(chs);
            PrintArray(strs);
        });
    }

#define CONST_REF_GETTER(member, nameInFunc)                                                       \
    const decltype(member) &Get##nameInFunc() const { return member; }
    CONST_REF_GETTER(testFuncs, TestFunctions)
#undef CONST_REF_GETTER
};

int main() {
    Tests tests;
    int item = 0;
    for (auto &[name, _] : tests.GetTestFunctions()) {
        std::cout << std::format("{} -> {}\n", item, name);
        ++item;
    }

    std::cin >> item;
    int i = 0;
    for (auto &[_, func] : tests.GetTestFunctions()) {
        if (i == item) {
            func();
            break;
        }
        ++i;
    }

    return 0;
}
