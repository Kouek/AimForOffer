#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/sliding-window-maximum/
 */

class Solution {
  public:
    std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
        std::deque<int> dq;
        for (int i = 0; i < k; ++i) {
            while (!dq.empty() && nums[dq.front()] <= nums[i])
                dq.pop_front();
            dq.emplace_back(i);
        }
        std::sort(dq.begin(), dq.end(), [&](int a, int b) { return nums[a] > nums[b]; });

        std::vector<int> ret;
        ret.reserve(nums.size() - k + 1);
        ret.emplace_back(nums[dq.front()]);

        for (int r = k; r < nums.size(); ++r) {
            while (!dq.empty() && nums[dq.back()] < nums[r])
                dq.pop_back();
            dq.emplace_back(r);
            while (dq.front() <= r - k)
                dq.pop_front();

            ret.emplace_back(nums[dq.front()]);
        }

        return ret;
    }
};

#include "shared/dummy_main.inl"
