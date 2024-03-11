#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/trapping-rain-water/
 */

class Solution {
  public:
    int trap(std::vector<int> &height) {
#ifdef NAIVE
        /*max_lft[i]=max(max_lft[i-1], height[i])
         * max_rht[i]=max(max_rht[i+1], height[i])
         */
        std::vector<int> maxLft(height.size(), 0);
        std::vector<int> maxRht(height.size(), 0);
        maxLft.front() = height.front();
        maxRht.back() = height.back();
        for (int i = 1; i < height.size(); ++i)
            maxLft[i] = std::max(maxLft[i - 1], height[i]);
        for (int i = height.size() - 2; i != -1; --i)
            maxRht[i] = std::max(maxRht[i + 1], height[i]);

        /*Water Height of i is
         * min(max_lft[i], max_rht[i]) - height[i]
         */
        int ret = 0;
        for (int i = 0; i < height.size() - 1; ++i)
            ret += std::min(maxLft[i], maxRht[i]) - height[i];
        return ret;
#else
        std::array maxs = {0, 0};
        std::array itrs = {height.begin(), height.end() - 1};
        int ret = 0;
        while (itrs[0] != itrs[1]) {
            maxs[0] = std::max(maxs[0], *itrs[0]);
            maxs[1] = std::max(maxs[1], *itrs[1]);

            if (maxs[0] < maxs[1])
                ret += maxs[0] - *itrs[0];
            else
                ret += maxs[1] - *itrs[1];

            if (*itrs[0] < *itrs[1])
                ++itrs[0];
            else
                --itrs[1];
        }
        return ret;
#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
