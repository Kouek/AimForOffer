#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/search-insert-position/
 */

class Solution {
  public:
    int searchInsert(std::vector<int> &nums, int target) {
#ifdef EASY
        auto itr = std::lower_bound(nums.begin(), nums.end(), target);
        return itr - nums.begin();
#endif // EASY
        auto lft = nums.begin();
        auto cnt = nums.size();
        while (cnt > 0) {
            auto mid = lft;
            auto cntNxt = cnt / 2;
            std::advance(mid, cntNxt);
            if (*mid < target) {
                lft = mid + 1;
                cnt -= cntNxt;
            } else
                cnt = cntNxt;
        }
        return lft - nums.begin();
    }
};

#include <shared/dummy_main.inl>
