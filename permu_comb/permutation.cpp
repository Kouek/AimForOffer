#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/permutations/
 */

class Solution {
  public:
    std::vector<std::vector<int>> permute(std::vector<int> &nums) {
        if (nums.empty())
            return {};
        
        std::vector<std::vector<int>> ret;
        auto backtrack = [&](auto&& recur, int lft) {
            if (lft == nums.size()) {
                ret.emplace_back(nums);
                return;
            }

            for (auto i = lft; i < nums.size(); ++i) {
                std::swap(nums[lft], nums[i]);
                recur(recur, lft + 1);
                std::swap(nums[lft], nums[i]);
            }
        };
        backtrack(backtrack, 0);

        return ret;
    }
};

#include <shared/dummy_main.inl>
