#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/search-in-rotated-sorted-array/
 */

class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        auto lft = nums.begin();
        auto rht = nums.end() - 1;

        while (lft <= rht) {
            auto cntOv2 = rht - lft + 1;
            cntOv2 /= 2;
            auto mid = lft;
            std::advance(mid, cntOv2);

            if (*mid == target)
                return mid - nums.begin();

            if (*lft <= *mid)
                if (*lft <= target && *mid > target)
                    rht = mid - 1;
                else
                    lft = mid + 1;
            else if (*mid < target && *rht >= target)
                lft = mid + 1;
            else
                rht = mid - 1;
        }

        return -1;
    }
};

#include <shared/dummy_main.inl>
