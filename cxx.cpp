#include <shared/all_stl.h>

#define PRINT_FUNC                                                                                 \
    {                                                                                              \
        auto srcLoc = std::source_location::current();                                             \
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),      \
                                 srcLoc.line());                                                   \
    }

class Object {
  public:
    int o = 0;

  public:
    virtual void Override() const { PRINT_FUNC; }
    void F() const { PRINT_FUNC; }

    virtual ~Object() {}
};
class A : virtual public Object {
  public:
    int a = 1;

  public:
    virtual void Override() const override { PRINT_FUNC; }
    void F() const { PRINT_FUNC; }
};
class B : virtual public Object {
  public:
    int b = 2;

  public:
    void Override() const { PRINT_FUNC; }
    void F() const { PRINT_FUNC; }
};
class ABChildObject : public A, public B {
  public:
    int o = 3;

  public:
    void Override() const { PRINT_FUNC; }
    void F() const { PRINT_FUNC; }
};

class SharedB;
class SharedA {
  public:
    SharedA() { PRINT_FUNC; }
    ~SharedA() { PRINT_FUNC; }
    void F() {
        if (shared)
            std::cout << std::format("shared addr: {:x}.\n",
                                     reinterpret_cast<size_t>(shared.get()));
    }

    std::shared_ptr<SharedB> shared;
};
class SharedB {
  public:
    SharedB() { PRINT_FUNC; }
    ~SharedB() { PRINT_FUNC; }
    void F() {
        if (shared)
            std::cout << std::format("shared addr: {:x}.\n",
                                     reinterpret_cast<size_t>(shared.get()));
    }

    std::shared_ptr<SharedA> shared;
};
class SharedC : public SharedB {
  public:
    SharedC() { PRINT_FUNC; }
    ~SharedC() { PRINT_FUNC; }
    void F() {
        if (!weak.expired()) {
            auto shared = weak.lock();
            std::cout << std::format("weak addr: {:x}.\n", reinterpret_cast<size_t>(shared.get()));
        } else
            std::cout << "weak addr: NULL\n";
    }

    std::weak_ptr<SharedA> weak;
};

static const int &OutlineMin(const int &a, const int &b) { return std::min(a, b); }
static const int &WrongCnstRefRet() {
    int b = 5;
    return b;
}

template <typename Num, typename... Nums> constexpr Num Product(Num num, Nums... nums) {
    if constexpr (sizeof...(nums) > 0)
        return num * Product(nums...);
    return num;
}
template <typename Num, size_t Cnt> constexpr Num ProductV2(Num (&&nums)[Cnt]) {
    Num ret = 1;
    for (auto num : nums)
        ret *= num;
    return ret;
}
template <typename... Nums> constexpr auto ProductV3(Nums... nums) { return (... * nums); }

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

#define LOG_CALL(call)                                                                             \
    {                                                                                              \
        std::cout << #call << ":\n\t";                                                             \
        call;                                                                                      \
    }

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Null", []() {
            struct A {
                void F(int) { PRINT_FUNC; }
                void F(uint8_t *) { PRINT_FUNC; }
            };
            A a;
            a.F(nullptr);
            a.F(NULL);
        });
        testFuncs.emplace("New Delete", []() {
            struct A {
                int x = 2333;
                A() { PRINT_FUNC; }
            };
            struct B {
                int x;
            };

            auto *a = new A;
            LOG_CALL(std::cout << a->x << '\n');
            delete a;

            a = new A();
            LOG_CALL(std::cout << a->x << '\n');
            delete a;

            auto *b = new B;
            LOG_CALL(std::cout << b->x << '\n');
            delete b;

            b = new B();
            LOG_CALL(std::cout << b->x << '\n');
            delete b;
        });
        testFuncs.emplace("New Delete []", []() {
            struct A {
                int x = 2333;
                A() { PRINT_FUNC; }
                ~A() { PRINT_FUNC; }
            };
            auto *as = new A[2];
            delete[] as;

            as = new A[2];
            delete as;
        });
        testFuncs.emplace("New Delete Virtual Destructor", []() {
            {
                struct A {
                    ~A() { PRINT_FUNC; }
                };
                struct B : A {
                    ~B() { PRINT_FUNC; }
                };
                A *bAsA = new B;
                delete bAsA;
            }
            {
                struct A {
                    virtual ~A() { PRINT_FUNC; }
                };
                struct B : A {
                    ~B() { PRINT_FUNC; }
                };
                A *bAsA = new B;
                delete bAsA;
            }
        });
        testFuncs.emplace("Make Unique", []() {
            struct A {
                int x = 2333;
                A() { PRINT_FUNC; }
            };
            struct B {
                int x;
            };

            auto a = std::make_unique<A>();
            LOG_CALL(std::cout << a->x << '\n');

            a = std::unique_ptr<A>(new A);
            LOG_CALL(std::cout << a->x << '\n');

            auto b = std::make_unique<B>();
            LOG_CALL(std::cout << b->x << '\n');

            b = std::unique_ptr<B>(new B);
            LOG_CALL(std::cout << b->x << '\n');
        });
        testFuncs.emplace("Memory Alignment", []() {
            struct A {
                int x;
                bool y;
            };
            constexpr auto AlignA = alignof(A);
            struct alignas([&]() {
                auto ret = AlignA;
                for (uint8_t i = 0; i < 3; ++i)
                    ret *= AlignA;
                return ret;
            }()) B {
                int x;
                bool y;
            };
            constexpr auto AlignB = alignof(B);
            {
                auto a = std::make_unique<A>();
                auto pAAddr = (size_t)a.get();
                LOG_CALL(std::cout << std::format("%{}:{}, %{}:{}\n", AlignA, (pAAddr % AlignA),
                                                  AlignB, (pAAddr % AlignB)));
            }
            {
                auto b = std::make_unique<B>();
                auto pAAddr = (size_t)b.get();
                LOG_CALL(std::cout << std::format("%{}:{}, %{}:{}\n", AlignA, (pAAddr % AlignA),
                                                  AlignB, (pAAddr % AlignB)));
            }
        });
        testFuncs.emplace("Overload Const", []() {
            struct A {
                A *self;
                A() : self(this) {}
                A *F() {
                    PRINT_FUNC;
                    return self;
                }
                const A *F() const {
                    PRINT_FUNC;
                    return self;
                }
            };
            A a;
            auto self = a.F();
            const A aCnst;
            auto selfCnst = aCnst.F();
        });
        testFuncs.emplace("Mutable Const", []() {
            int x = 0;
            auto mtbl = [=]() mutable {
                ++x;
                std::cout << std::format("{:x}:{}\n", (size_t)&x, x);
            };
            auto normal = [&]() {
                ++x;
                std::cout << std::format("{:x}:{}\n", (size_t)&x, x);
            };
            LOG_CALL(mtbl());
            LOG_CALL(normal());
            LOG_CALL(normal());
            LOG_CALL(mtbl());

            struct Mutable {
                mutable int x;
                void operator()() const {
                    ++x;
                    std::cout << std::format("{:x}:{}\n", (size_t)&x, x);
                }
            };
            Mutable myMtbl = {x};
            LOG_CALL(myMtbl());
            LOG_CALL(myMtbl());
        });
        testFuncs.emplace("Explicit", []() {
            struct A {
                explicit A(int x) { PRINT_FUNC; }
            };
            struct B {
                B(int x) { PRINT_FUNC; }
            };
            // A a = 1;
            B b = 1;
        });
        testFuncs.emplace("Universal Reference", []() {
            struct A {
                A() = default;
                A(const A &) { PRINT_FUNC; }
                A(A &&) { PRINT_FUNC; }
            };
            A a;
            WrongCastFromUniRef(a);
            CorrectCastFromUniRef(a);
            WrongCastFromUniRef(std::move(a));
            CorrectCastFromUniRef(std::move(a));
        });
        testFuncs.emplace("Dynamic Polymorphism", []() {
            std::cout << "\nTest A\n";
            std::unique_ptr<Object> pA = std::make_unique<A>();
            LOG_CALL(pA->Override());
            LOG_CALL(dynamic_cast<A *>(pA.get())->Override());
            LOG_CALL(pA->F());
            LOG_CALL(dynamic_cast<A *>(pA.get())->F());

            std::cout << "\nTest B\n";
            std::unique_ptr<Object> pB = std::make_unique<B>();
            LOG_CALL(pB->Override());
            LOG_CALL(dynamic_cast<B *>(pB.get())->Override());
            LOG_CALL(pB->F());
            LOG_CALL(dynamic_cast<B *>(pB.get())->F());

            std::cout << "\nTest ABChild\n";
            std::unique_ptr<Object> pABCh = std::make_unique<ABChildObject>();
            LOG_CALL(pABCh->Override());
            LOG_CALL(dynamic_cast<ABChildObject *>(pABCh.get())->Override());
            LOG_CALL(dynamic_cast<A *>(pABCh.get())->Override());
            LOG_CALL(dynamic_cast<B *>(pABCh.get())->Override());
            LOG_CALL(pABCh->F());
            LOG_CALL(dynamic_cast<ABChildObject *>(pABCh.get())->F());
            LOG_CALL(dynamic_cast<A *>(pABCh.get())->F());
            LOG_CALL(dynamic_cast<B *>(pABCh.get())->F());

            LOG_CALL(std::cout << pABCh->o << '\n');
            LOG_CALL(std::cout << dynamic_cast<ABChildObject *>(pABCh.get())->o << '\n');
        });
        testFuncs.emplace("Dynamic Polymorphism Side Cast", []() {
            std::unique_ptr<A> pABChAsA = std::make_unique<ABChildObject>();
            LOG_CALL(pABChAsA->Override());
            LOG_CALL(dynamic_cast<ABChildObject *>(pABChAsA.get())->Override());
            LOG_CALL(dynamic_cast<B *>(pABChAsA.get())->Override());
            LOG_CALL(dynamic_cast<Object *>(pABChAsA.get())->Override());
            LOG_CALL(pABChAsA->F());
            LOG_CALL(dynamic_cast<ABChildObject *>(pABChAsA.get())->F());
            LOG_CALL(dynamic_cast<B *>(pABChAsA.get())->F());
            LOG_CALL(dynamic_cast<Object *>(pABChAsA.get())->F());

            LOG_CALL(std::cout << pABChAsA->o << '\n');
            LOG_CALL(std::cout << dynamic_cast<ABChildObject *>(pABChAsA.get())->o << '\n');
            LOG_CALL(std::cout << dynamic_cast<B *>(pABChAsA.get())->o << '\n');
            LOG_CALL(std::cout << dynamic_cast<Object *>(pABChAsA.get())->o << '\n');
        });
        testFuncs.emplace("Dynamic Polymorphism with Reference", []() {
            auto ref = [](const auto &ref) {
                LOG_CALL(ref.Override());
                LOG_CALL(ref.F());
            };

            ABChildObject abCh;
            ref(abCh);
            ref(dynamic_cast<const A &>(abCh));
            ref(dynamic_cast<const B &>(abCh));
        });
        testFuncs.emplace("Dynamic Polymorphism Offset", []() {
            auto pt = [](const auto *ptr) {
                ptr->F();
                auto *p1 = (const uint8_t *)ptr;
                auto *p0 = (const uint8_t *)dynamic_cast<const Object *>(ptr);
                std::cout << std::format("\t{}\n", p1 - p0);
            };

            std::unique_ptr<Object> pABCh = std::make_unique<ABChildObject>();
            pt(pABCh.get());
            pt(dynamic_cast<const A *>(pABCh.get()));
            pt(dynamic_cast<const B *>(pABCh.get()));
            pt(dynamic_cast<const ABChildObject *>(pABCh.get()));
        });
        testFuncs.emplace("Shared Pointer", []() {
            std::cout << "\nTest Circular Sharing\n";
            SharedA *a = nullptr;
            {
                auto shrdA = std::make_shared<SharedA>();
                auto shrdB = std::make_shared<SharedB>();
                shrdA->shared = shrdB;
                shrdB->shared = shrdA;
                shrdA->F();
                shrdB->F();

                a = shrdA.get();
            }
            a->F();
            a->shared->F();

            std::cout << "\nTest Weak Sharing\n";
            auto shrdC = std::make_shared<SharedC>();
            {
                auto shrdA = std::make_shared<SharedA>();
                shrdA->shared = shrdC;
                shrdC->weak = shrdA;
                shrdA->F();
                shrdC->F();
            }
            shrdC->F();
        });
        testFuncs.emplace("Constexpr", []() {
            int a = 10;
            constexpr int b = 5;
            auto &x = OutlineMin(a, b);
            std::cout << std::format("x:{}\n", x);

            auto &xx = OutlineMin(a, WrongCnstRefRet());
            std::cout << std::format("xx:{}\n", xx);
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
        });
        testFuncs.emplace("Array", []() {
            std::array chs = {'a', 'b','c'};
            //std::array chs = {'a', 'b', 0};
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

int main(int argc, char **argv) {
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
