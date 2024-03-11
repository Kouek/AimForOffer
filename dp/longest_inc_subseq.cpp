#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/longest-increasing-subsequence/
 */

class Solution {
  public:
    int lengthOfLIS(std::vector<int> &nums) {
#ifdef NAIVE
        std::vector<int> dp(nums.size(), 1);

        auto ret = 1;
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j)
                if (nums[i] > nums[j])
                    dp[i] = std::max(dp[i], dp[j] + 1);
            ret = std::max(ret, dp[i]);
        }

        return ret;
#else
        std::vector<int> ansSeq;
        ansSeq.emplace_back(nums[0]);

        for (int i = 1; i < nums.size(); ++i) {
            //auto itr = std::lower_bound(ansSeq.begin(), ansSeq.end(), nums[i]);
            auto itr = [&](int num) {
                auto lft = ansSeq.begin();
                auto cnt = ansSeq.size();
                while (cnt > 0) {
                    auto cntNxt = cnt / 2;
                    auto mid = lft + cntNxt;
                    if (*mid < num) {
                        lft = mid + 1;
                        cnt = cnt - cntNxt - 1;
                    } else
                        cnt = cntNxt;
                }
                return lft;
            }(nums[i]);

            if (itr == ansSeq.end()) {
                ansSeq.emplace_back(nums[i]);
                continue;
            }

            *itr = nums[i];
        }

        return ansSeq.size();
#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
