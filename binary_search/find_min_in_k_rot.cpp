#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/
 */

class Solution {
  public:
    int findMin(std::vector<int> &nums) {
        if (nums.size() == 1)
            return nums.front();

        auto lft = nums.begin();
        auto rht = nums.end() - 1;

        while (lft < rht) {
            auto mid = lft + (rht - lft + 1) / 2;
            
            if (*lft < *mid)
                if (*mid <= *rht)
                    rht = mid - 1;
                else
                    lft = mid + 1;
            else if (mid == rht) {
                ++lft;
                break;
            } else
                rht = mid;
        }
        return *lft;
    }
};

#include <shared/dummy_main.inl>
