#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/min-stack/
 */

class MinStack {
  private:
    std::stack<std::tuple<int, int>> stk;

  public:
    MinStack() {}

    void push(int val) {
        if (stk.empty())
            stk.emplace(val, val);
        else
            stk.emplace(val, std::min(val, std::get<1>(stk.top())));
    }

    void pop() { stk.pop(); }

    int top() { return std::get<0>(stk.top()); }

    int getMin() { return std::get<1>(stk.top()); }
};

#include <shared/dummy_main.inl>
