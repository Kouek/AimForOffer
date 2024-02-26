#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/median-of-two-sorted-arrays/
 */

class Solution {
  public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        /*Given nums[n], the median is
         * nums[n/2] if n is odd or
         * 0.5 * (nums[n/2] + nums[n/2+1]) if n is even
         */

        auto findKthSmallest = [&](int k) -> double {
            std::array itrs = {nums1.begin(), nums2.begin()};
            while (true) {
                if (itrs[0] == nums1.end())
                    return *(itrs[1] + k - 1);
                if (itrs[1] == nums2.end())
                    return *(itrs[0] + k - 1);
                if (k == 1)
                    return std::min(*itrs[0], *itrs[1]);

                std::array newItrs = {itrs[0] + k / 2 - 1, itrs[1] + k / 2 - 1};
                if (newItrs[0] >= nums1.end())
                    newItrs[0] = nums1.end() - 1;
                if (newItrs[1] >= nums2.end())
                    newItrs[1] = nums2.end() - 1;

                if (*newItrs[0] <= *newItrs[1]) {
                    k -= newItrs[0] - itrs[0] + 1;
                    itrs[0] = newItrs[0] + 1;
                } else {
                    k -= newItrs[1] - itrs[1] + 1;
                    itrs[1] = newItrs[1] + 1;
                }
            }
        };

        int totNum = nums1.size() + nums2.size();
        if (totNum % 2 == 1)
            return findKthSmallest(totNum / 2 + 1);
        else
            return 0.5 * (findKthSmallest(totNum / 2) + findKthSmallest(totNum / 2 + 1));
    }
};

#include "shared/dummy_main.inl"
