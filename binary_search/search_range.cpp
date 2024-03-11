#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 */

class Solution {
  public:
    std::vector<int> searchRange(std::vector<int> &nums, int target) {
        auto lft = nums.begin();
        auto cnt = nums.size();

        while (cnt > 0) {
            auto cntNxt = cnt / 2;
            auto mid = lft + cntNxt;
            if (*mid < target) {
                lft = mid + 1;
                cnt = cnt - cntNxt - 1;
            } else
                cnt = cntNxt;
        }
        if (lft == nums.end() || *lft != target)
            return {-1, -1};

        auto rht = lft;
        cnt = nums.end() - rht;
        while (cnt > 0) {
            auto cntNxt = cnt / 2;
            auto mid = rht + cntNxt;
            if (*mid <= target) {
                rht = mid + 1;
                cnt = cnt - cntNxt - 1;
            } else
                cnt = cntNxt;
        }
        return {static_cast<int>(lft - nums.begin()), static_cast<int>(rht - 1 - nums.begin())};
    }
};

#include <shared/dummy_main.inl>
