#include "shared/all_stl.h"

class Object {
  public:
    virtual void Override() {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
    void f() {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
};

class AObject : public Object {
  public:
    virtual void Override() override {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
    void f() {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
};

class BObject : public Object {
  public:
    void Override() {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
    void f() {
        auto srcLoc = std::source_location::current();
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),
                                 srcLoc.line());
    }
};

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Dynamic Polymorphism", []() {
            std::unique_ptr<Object> pA = std::make_unique<AObject>();
            pA->Override();
            dynamic_cast<AObject *>(pA.get())->Override();
            pA->f();
            dynamic_cast<AObject *>(pA.get())->f();

            std::unique_ptr<Object> pB = std::make_unique<BObject>();
            pB->Override();
            dynamic_cast<BObject *>(pB.get())->Override();
            pB->f();
            dynamic_cast<BObject *>(pB.get())->f();
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
