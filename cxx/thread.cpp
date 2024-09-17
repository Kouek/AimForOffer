#include <shared/all_stl.h>

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        using namespace std::chrono_literals;
        constexpr int ThreadNum = 1024;
        constexpr int Threshold = 22;

        testFuncs.emplace("Thread", []() {
            std::vector<std::thread> threads;
            threads.reserve(ThreadNum);
            auto pShrdSum = std::make_shared<int>(0);
            for (int i = 0; i < ThreadNum; ++i) {
                threads.emplace_back([pShrdSum, i]() {
                    auto loaded = *pShrdSum;
                    if (loaded < Threshold)
                        ++(*pShrdSum);
                });
            }
            for (auto &thread : threads)
                thread.join();
            LOG_CALL(std::cout << *pShrdSum << '\n');
        });
        testFuncs.emplace("Join Thread", []() {
            auto pShrdSum = std::make_shared<int>(0);
            {
                std::vector<std::jthread> threads;
                threads.reserve(ThreadNum);
                for (int i = 0; i < ThreadNum; ++i) {
                    threads.emplace_back([pShrdSum, i]() {
                        auto loaded = *pShrdSum;
                        if (loaded < Threshold)
                            ++(*pShrdSum);
                    });
                }
            }
            LOG_CALL(std::cout << *pShrdSum << '\n');
        });
        testFuncs.emplace("Atomic Shared Pointer", []() {
            std::atomic pAtomicShrdSum = std::make_shared<int>(0);
            {
                std::vector<std::jthread> threads;
                threads.reserve(ThreadNum);
                for (int i = 0; i < ThreadNum; ++i) {
                    threads.emplace_back([&pAtomicShrdSum, i]() {
                        auto pShrdSum = pAtomicShrdSum.load();
                        auto loaded = *pShrdSum;
                        if (loaded < Threshold)
                            ++(*pShrdSum);
                    });
                }
            }
            LOG_CALL(std::cout << *(pAtomicShrdSum.load()) << '\n');
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
