#include <shared/all_stl.h>

class Friend {
    int a = 123;

  public:
    friend int VisitFriend(const Friend &fr) { return fr.a; }
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
struct SharedD {
    std::shared_ptr<SharedD> Self() { return std::shared_ptr<SharedD>(this); }
};

struct IntegerIterator {
    int num;

    IntegerIterator(int at) : num(at) {}

    IntegerIterator operator++() {
        ++num;
        return *this;
    }
    IntegerIterator operator++(int) {
        auto curr = *this;
        ++num;
        return curr;
    }
    int &operator*() { return num; }
    bool operator==(const IntegerIterator &other) const { return num == other.num; }
};

static const int &OutlineMin(const int &a, const int &b) { return std::min(a, b); }
static const int &WrongCnstRefRet() {
    int b = 5;
    return b;
}

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Construction", []() {
            struct A {
                int a = 1;

                A() { PRINT_FUNC; }
                A(const A &a) {
                    PRINT_FUNC;
                    this->a = a.a;
                }
                A &operator=(const A &a) {
                    PRINT_FUNC;
                    this->a = a.a;

                    return *this;
                }
            };

            A a1;
            A a2 = a1;
        });
        testFuncs.emplace("Construction of Template", []() {
            struct A {
                int a;
                float b;
                double c;

                A(int a, float b, double c) : a(a), b(b), c(c) { PRINT_FUNC; }
                A(const A &a) {
                    PRINT_FUNC;
                    this->a = a.a;
                }
                A &operator=(const A &a) {
                    PRINT_FUNC;
                    this->a = a.a;

                    return *this;
                }
            };

            std::vector<A> as;
            auto func = [&]<typename... Args>(auto &&a, Args &&...args) {
                as.emplace_back(a, args...);
            };
            func(20, 6.3f, 18.9);
            LOG_CALL(std::cout << as[0].a << std::endl);
            LOG_CALL(std::cout << as[0].b << std::endl);
            LOG_CALL(std::cout << as[0].c << std::endl);
        });
        testFuncs.emplace("Null", []() {
            struct A {
                void F(int) { PRINT_FUNC; }
                void F(uint8_t *) { PRINT_FUNC; }
            };
            A a;
            a.F(nullptr);
            a.F(NULL);
        });
        testFuncs.emplace("Friend", []() {
            Friend fr;
            LOG_CALL(std::cout << VisitFriend(fr) << '\n');
        });
        testFuncs.emplace("New Delete", []() {
            struct A {
                int x = 2333;
                A() { PRINT_FUNC; }
            };
            struct B {
                int x;
            };
            struct C {
                int x = 1;
                void *operator new(size_t x) {
                    PRINT_FUNC;
                    return ::new C;
                }
                void operator delete(void *addr) {
                    PRINT_FUNC;
                    ::delete static_cast<C *>(addr);
                }
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

            auto *c = new C;
            delete c;
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
        testFuncs.emplace("New Delete Destructor", []() {
            struct A {
                ~A() { PRINT_FUNC; }
            };
            struct B : A {
                ~B() { PRINT_FUNC; }
            };
            auto *b = new B;
            LOG_CALL(delete b);
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
                LOG_CALL(delete bAsA);
                std::unique_ptr<A> uniBAsA = std::make_unique<B>();
                LOG_CALL(uniBAsA.reset());
                std::shared_ptr<A> shrdBAsA = std::make_shared<B>();
                LOG_CALL(shrdBAsA.reset());
            }
            {
                struct A {
                    virtual ~A() { PRINT_FUNC; }
                };
                struct B : A {
                    ~B() { PRINT_FUNC; }
                };
                A *bAsA = new B;
                LOG_CALL(delete bAsA);
                std::unique_ptr<A> uniBAsA = std::make_unique<B>();
                LOG_CALL(uniBAsA.reset());
                std::shared_ptr<A> shrdBAsA = std::make_shared<B>();
                LOG_CALL(shrdBAsA.reset());
            }
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
                LOG_CALL(std::cout << std::format("{}, {}\n", (size_t)(&a->x) - pAAddr,
                                                  (size_t)(&a->y) - pAAddr));
            }
            {
                auto b = std::make_unique<B>();
                auto pBAddr = (size_t)b.get();
                LOG_CALL(std::cout << std::format("%{}:{}, %{}:{}\n", AlignA, (pBAddr % AlignA),
                                                  AlignB, (pBAddr % AlignB)));
                LOG_CALL(std::cout << std::format("{}, {}\n", (size_t)(&b->x) - pBAddr,
                                                  (size_t)(&b->y) - pBAddr));
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
        testFuncs.emplace("Functions with Same Name", []() {
            class A {
              public:
                virtual void FuncA() { PRINT_FUNC; }

                // static void FuncA() { PRINT_FUNC; }
                static void FuncC() { PRINT_FUNC; }
            };
            class B : public A {
              public:
                virtual void FuncB() { PRINT_FUNC; }
                virtual void FuncC() { PRINT_FUNC; }

                static void FuncA() { PRINT_FUNC; }
                // static void FuncB() { PRINT_FUNC; }
            };

            std::unique_ptr<A> pBAsA = std::make_unique<B>();
            LOG_CALL(pBAsA->FuncA());
            LOG_CALL(static_cast<B *>(pBAsA.get())->FuncB());
            LOG_CALL(static_cast<B *>(pBAsA.get())->FuncC());
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
        testFuncs.emplace("Noexcept", []() {
            struct A {
                void F() noexcept { throw 1; }
            };
            try {
                A a;
                a.F();
            } catch (int v) {
                std::cout << v << '\n';
            }
        });
        testFuncs.emplace("RAII Exception", []() {
            struct A {
                int *x = nullptr;
                A() {
                    PRINT_FUNC;
                    x = new int();
                }
                ~A() {
                    PRINT_FUNC;
                    delete x;
                }
            };
            try {
                A a;
                throw 1;
            } catch (int v) {
                std::cout << v << '\n';
            }
        });
        testFuncs.emplace("Unique Pointer Copy", []() {
            struct A {
                size_t num;
                int *dat = nullptr;

                A(size_t num) : num(num) {
                    PRINT_FUNC;
                    dat = new int[num];
                }
                A(const A &other) {
                    PRINT_FUNC;

                    if (dat)
                        delete[] dat;

                    num = other.num;
                    dat = new int[num];
                }
                ~A() {
                    std::cout << std::format("Destruction: dat: {:x}\n",
                                             reinterpret_cast<ptrdiff_t>(dat));

                    if (dat)
                        delete[] dat;
                }
            };

            {
                auto pA1 = std::make_unique<A>(100);
                auto pA2 = std::make_unique<A>(*pA1.get());
            }
        });
        testFuncs.emplace("Unique Pointer Make Unique", []() {
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
        testFuncs.emplace("Shared Pointer", []() {
            std::cout << "\nTest Circular Sharing\n";
            SharedA *a = nullptr;
            {
                auto shrdA = std::make_shared<SharedA>();
                auto shrdB = std::make_shared<SharedB>();
                shrdA->shared = shrdB;
                shrdB->shared = shrdA;
                LOG_CALL(shrdA->F());
                LOG_CALL(shrdB->F());

                a = shrdA.get();
            }
            LOG_CALL(a->F());
            LOG_CALL(a->shared->F());

            std::cout << "\nTest Weak Sharing\n";
            auto shrdC = std::make_shared<SharedC>();
            {
                auto shrdA = std::make_shared<SharedA>();
                shrdA->shared = shrdC;
                shrdC->weak = shrdA;
                LOG_CALL(shrdA->F());
                LOG_CALL(shrdC->F());
            }
            LOG_CALL(shrdC->F());

            std::cout << "\nTest Self Sharing\n";
            auto shrdD = std::make_shared<SharedD>();
            auto shrdDD = shrdD->Self();
            LOG_CALL(std::cout << std::format("{},{}\n", shrdD.use_count(), shrdDD.use_count()));
        });
        testFuncs.emplace("Constexpr", []() {
            int a = 10;
            constexpr int b = 5;
            auto &x = OutlineMin(a, b);
            std::cout << std::format("x:{}\n", x);

            auto &xx = OutlineMin(a, WrongCnstRefRet());
            std::cout << std::format("xx:{}\n", xx);
        });
        testFuncs.emplace("Integer Iterator", []() {
            LOG_CALL(std::cout << std::accumulate(IntegerIterator(0), IntegerIterator(10), 0)
                               << '\n');
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
