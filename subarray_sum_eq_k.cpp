#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/subarray-sum-equals-k/
 */

class Solution {
  public:
    int subarraySum(std::vector<int> &nums, int k) {
        std::unordered_map<int, int> cnts;
        int prefixSum = 0;
        cnts[0] = 1;
        int ret = 0;
        for (auto num : nums) {
            prefixSum += num;
            if (auto itr = cnts.find(prefixSum - k); itr != cnts.end())
                ret += itr->second;
            if (auto itr = cnts.find(prefixSum); itr != cnts.end())
                ++itr->second;
            else
                cnts[prefixSum] = 1;
        }
        return ret;
    }
};

#include "shared/dummy_main.inl"
