#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/combination-sum/
 */

class Solution {
  public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        if (candidates.empty())
            return {};

        std::vector<std::vector<int>> ret;
        std::vector<int> ans;
        auto search = [&](auto &&recur, int i, int remain) {
            if (i == candidates.size())
                return;
            if (remain == 0) {
                ret.emplace_back(ans);
                return;
            }

            if (remain - candidates[i] >= 0) {
                ans.emplace_back(candidates[i]);
                recur(recur, i, remain - ans.back());
                ans.pop_back();
            }
            recur(recur, i + 1, remain);
        };
        search(search, 0, target);

        return ret;
    }
};

#include <shared/dummy_main.inl>
