#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/house-robber/
 */

class Solution {
  public:
    int rob(std::vector<int> &nums) {
        if (nums.size() == 1)
            return nums.front();
        if (nums.size() == 2)
            return std::max(nums.front(), nums.back());

        // f[i] = max( f[i] + f[i-2], f[i-1] )
        std::vector<int> moneys(nums.size(), 0);
        moneys[0] = nums[0];
        moneys[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i)
            moneys[i] = std::max(moneys[i - 2] + nums[i], moneys[i - 1]);

        return moneys.back();
    }
};

#include <shared/dummy_main.inl>
