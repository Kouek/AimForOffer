#include <algorithm>
#include <atomic>
#include <bit>
#include <format>
#include <functional>
#include <iostream>
#include <numeric>
#include <source_location>
#include <string>

#include <array>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define PRINT_FUNC                                                                                 \
    {                                                                                              \
        auto srcLoc = std::source_location::current();                                             \
        std::cout << std::format("{} at {}:{}\n", srcLoc.function_name(), srcLoc.file_name(),      \
                                 srcLoc.line());                                                   \
    }

#define LOG_CALL(call)                                                                             \
    {                                                                                              \
        std::cout << #call << ":\n\t";                                                             \
        call;                                                                                      \
    }
