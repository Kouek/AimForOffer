#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/kth-largest-element-in-an-array/
 */

class Solution {
  public:
    int findKthLargest(std::vector<int> &nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
        for (int i = 0; i < k; ++i)
            heap.emplace(nums[i]);

        for (int i = k; i < nums.size(); ++i) {
            if (nums[i] <= heap.top())
                continue;

            heap.pop();
            heap.emplace(nums[i]);
        }

        return heap.top();
    }
};

#include <shared/dummy_main.inl>
