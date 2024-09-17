#include <shared/all_stl.h>

struct Base0 {
    int base = 0;

    virtual ~Base0() {}
    virtual void F() { PRINT_FUNC; }
    void G() { PRINT_FUNC; }
};

struct Base1 {
    int base = 1;

    virtual ~Base1() {}
    void F() { PRINT_FUNC; }
    virtual void G() { PRINT_FUNC; }
};

struct Derived0 : virtual Base0 {
    int derived = 2;

    void F() override { PRINT_FUNC; }
    void G() { PRINT_FUNC; }
};

struct Derived0x1 : Base0, Base1 {
    int derived0x1 = 3;

    void F() override { PRINT_FUNC; }
    void G() override { PRINT_FUNC; }
    virtual void H() { PRINT_FUNC; }
};

struct Derived01 : virtual Base0 {
    int derived1 = 2;

    void F() override { PRINT_FUNC; }
    void G() { PRINT_FUNC; }
};

struct Derived0xDerived01 : Derived0, Derived01 {
    int derived0x1 = 3;

    void F() override { PRINT_FUNC; }
    virtual void H() { PRINT_FUNC; }
};

struct DerivedNonVirtual0 : Base0 {
    int derived = 2;

    void F() override { PRINT_FUNC; }
    void G() { PRINT_FUNC; }
};

struct DerivedNonVirtual01 : Base0 {
    int derived1 = 2;

    void F() override { PRINT_FUNC; }
    void G() { PRINT_FUNC; }
};

struct DerivedNonVirtual0xDerivedNonVirtual01 : DerivedNonVirtual0, DerivedNonVirtual01 {
    int derived0x1 = 3;

    void F() override { PRINT_FUNC; }
    virtual void H() { PRINT_FUNC; }
};

// template <typename DstTy, typename SrcTy> DstTy *Cast(SrcTy *srcPtr) {}

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Type ID", []() {
            Derived0x1 d0x1;
            auto *pBase0 = static_cast<Base0 *>(&d0x1);
            auto *pBase1 = static_cast<Base1 *>(&d0x1);
            LOG_CALL(std::cout << typeid(d0x1).name() << '\n');
            LOG_CALL(std::cout << typeid(*pBase0).name() << '\n');
            LOG_CALL(std::cout << typeid(*pBase1).name() << '\n');
            LOG_CALL(std::cout << typeid(&d0x1).name() << '\n');
            LOG_CALL(std::cout << typeid(pBase0).name() << '\n');
            LOG_CALL(std::cout << typeid(pBase1).name() << '\n');

            /*struct NoVirtualFunc {
                int x;
            };
            LOG_CALL(std::cout << typeid(NoVirtualFunc) << '\n');*/
        });
        testFuncs.emplace("Dynamic Cast", []() {
            auto pUniD0x1 = std::make_unique<DerivedNonVirtual0xDerivedNonVirtual01>();
            LOG_CALL(std::cout << pUniD0x1.get() << '\n');
            LOG_CALL(std::cout << dynamic_cast<DerivedNonVirtual0 *>(pUniD0x1.get()) << '\n');
            LOG_CALL(std::cout << dynamic_cast<Derived0 *>(pUniD0x1.get()) << '\n');
            LOG_CALL(std::cout << dynamic_cast<Base0 *>(pUniD0x1.get()) << '\n');
        });
        testFuncs.emplace("Static Cast", []() {
            auto pUniD0x1 = std::make_unique<Derived0x1>();
            LOG_CALL(std::cout << pUniD0x1.get() << '\n');

            LOG_CALL(std::cout << static_cast<Base0 *>(pUniD0x1.get()) << '\n');
            LOG_CALL(static_cast<Base0 *>(pUniD0x1.get())->F());
            Base0 *pBase0 = pUniD0x1.get();
            LOG_CALL(std::cout << pBase0 << '\n');
            LOG_CALL(pBase0->F());

            LOG_CALL(std::cout << static_cast<Base1 *>(pUniD0x1.get()) << '\n');
            LOG_CALL(static_cast<Base1 *>(pUniD0x1.get())->G());
            Base1 *pBase1 = pUniD0x1.get();
            LOG_CALL(std::cout << pBase1 << '\n');
            LOG_CALL(pBase1->G());
        });
        testFuncs.emplace("Reinterpret Cast", []() {
            auto pUniD0x1 = std::make_unique<Derived0x1>();
            LOG_CALL(std::cout << pUniD0x1.get() << '\n');

            LOG_CALL(std::cout << reinterpret_cast<Base0 *>(pUniD0x1.get()) << '\n');
            reinterpret_cast<Base0 *>(pUniD0x1.get())->F();

            LOG_CALL(std::cout << reinterpret_cast<Base1 *>(pUniD0x1.get()) << '\n');
            reinterpret_cast<Base1 *>(pUniD0x1.get())->G();
        });
        testFuncs.emplace("Cast", []() {
            std::unique_ptr<Base0> pUniD0x1AsBase0 = std::make_unique<Derived0x1>();
            pUniD0x1AsBase0->F();
            /*auto *pD0x1 = Cast<Derived0x1>(pUniD0x1AsBase0.get());
            pD0x1->F();*/

            std::unique_ptr<Base0> pUniD0xD01AsBase0 = std::make_unique<Derived0xDerived01>();
            pUniD0xD01AsBase0->F();
            /*auto *pD0x1 = Cast<Derived0xDerived01>(pUniD0x1AsBase0.get());
            pD0x1->F();*/
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
