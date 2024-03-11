#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/subsets/
 */

class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        if (nums.empty())
            return {};

        std::vector<std::vector<int>> ret; 
        for (int bit = 0; bit < (1 << (int)nums.size()); ++bit) {
            auto &v = ret.emplace_back();
            for (int i = 0; i < nums.size(); ++i)
                if (((bit >> i) & 0b1) != 0)
                    v.emplace_back(nums[i]);
        }
        
        return ret;
    }
};

#include <shared/dummy_main.inl>
