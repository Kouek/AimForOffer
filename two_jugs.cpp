#include "shared/all_stl.h"

/*URL:
* https://leetcode.cn/problems/water-and-jug-problem/submissions/508914417/
*/

class Solution {
  public:
    bool canMeasureWater(int x, int y, int target) {
        std::vector<bool> vists;
        std::stack<std::tuple<int, int>> stk;
        stk.emplace(0, 0);

        vists.assign((x + 1) * (y + 1), false);
        vists[0] = true;
        auto map = [&](int a, int b) { return a * (y + 1) + b; };
        while (!stk.empty()) {
            auto [a, b] = stk.top();
            stk.pop();
            std::cout << std::format("{},{}-> ", a, b);
            if (a == target || b == target || a + b == target)
                return true;

            auto move = [&](int a, int b) {
                if (a >= 0 && a <= x && b >= 0 && b <= y && !vists[map(a, b)]) {
                    stk.emplace(a, b);
                    vists[map(a, b)] = true;
                    return true;
                }
                return false;
            };
            move(0, b);
            move(x, b);
            move(a, 0);
            move(a, y);

            if (a <= y - b)
                move(0, b + a);
            else
                move(a - (y - b), y);

            if (b <= x - a)
                move(a + b, 0);
            else
                move(x, b - (x - a));
        }

        return false;
    }
};

int main() {
    Solution().canMeasureWater(3, 5, 4);

    return 0;
}