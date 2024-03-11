#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/maximum-product-subarray/
 */

class Solution {
  public:
    int maxProduct(std::vector<int> &nums) {
        int prodMin = nums[0];
        int prodMax = nums[0];

        auto max = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            auto num = nums[i];
            auto minMulNum = prodMin * num;
            auto maxMulNum = prodMax * num;
            prodMax = std::max({num, num < 0 ? minMulNum : maxMulNum});
            prodMin = std::min({num, num < 0 ? maxMulNum : minMulNum});

            max = std::max(max, prodMax);
        }

        return max;
    }
};

#include <shared/dummy_main.inl>
