#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/coin-change/
 */

class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        // f[i] = min( for each c in coins: f[i-c] + 1 )
        std::vector<int> minNums(amount + 1, std::numeric_limits<int>::max());
        minNums[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (auto coin : coins) {
                auto k = i - coin;
                if (k >= 0)
                    if (minNums[i] > minNums[k] + 1 && minNums[k] >= 0)
                        minNums[i] = minNums[k] + 1;
            }
            if (minNums[i] == std::numeric_limits<int>::max())
                minNums[i] = -1;
        }

        return minNums.back();
    }
};


// #include <shared/dummy_main.inl>

int main() {
    std::vector a = {2};
    Solution().coinChange(a, 3);
}
