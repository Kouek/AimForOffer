#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/maximum-subarray/
 */

class Solution {
  public:
    int maxSubArray(std::vector<int> &nums) {
        /*maxSumWithTail[i]
        * = maxSumWithTail[i-1] + nums[i] with maxSumWithTail[i-1] > 0 OR
        * = nums[i] with maxSumWithTail[i-1] <= 0
        * maxSumWithTail[i] = max(maxSumWithTail[i-1] + nums[i], nums[i])
        */
        int prevMaxSumWithTail = nums[0];
        int maxVal = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (prevMaxSumWithTail <= 0)
                prevMaxSumWithTail = nums[i];
            else
                prevMaxSumWithTail += nums[i];
            maxVal = std::max(prevMaxSumWithTail, maxVal);
        }

        return maxVal;
    }
};

#include "shared/dummy_main.inl"
