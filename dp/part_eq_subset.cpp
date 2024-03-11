#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/partition-equal-subset-sum/
 */

class Solution {
  public:
    bool canPartition(std::vector<int> &nums) {
        if (nums.size() <= 1)
            return false;

        auto sum = std::accumulate(nums.begin(), nums.end(), 0);
        auto max = *std::max(nums.begin(), nums.end() - 1);
        if (sum % 2 != 0)
            return false;
        sum /= 2;
        if (max > sum)
            return false;

        std::vector<bool> dp(nums.size() * (sum + 1), false);
        auto map = [&](int i, int target) -> decltype(dp)::reference {
            return dp[i * (sum + 1) + target];
        };

        for (int i = 0; i < nums.size(); ++i)
            map(i, 0) = true;
        map(0, nums[0]) = true;

        for (int target = 1; target <= sum; ++target) {
            for (int i = 1; i < nums.size(); ++i) {
                if (map(i - 1, target)) {
                    map(i, target) = true;
                    continue;
                }
                if (nums[i] <= target && map(i - 1, target - nums[i])) {
                    map(i, target) = true;
                    continue;
                }
            }
        }

        return map(nums.size() - 1, sum);
    }
};

// #include <shared/dummy_main.inl>

int main() {
    std::vector<int> x = {2, 2, 3, 5};
    Solution().canPartition(x);
}
