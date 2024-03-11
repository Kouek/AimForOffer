#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/merge-intervals/
 */

class Solution {
  public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals) {
        if (intervals.size() <= 1)
            return intervals;

        using Interval = std::array<int, 2>;
        std::vector<Interval> sortedIntrvls;
        sortedIntrvls.reserve(intervals.size());
        for (auto &vec : intervals)
            sortedIntrvls.push_back({vec[0], vec[1]});
        std::sort(sortedIntrvls.begin(), sortedIntrvls.end(),
                  [](const Interval &a, const Interval &b) { return a[0] < b[0]; });

        auto rht = sortedIntrvls.begin() + 1;
        std::vector<std::vector<int>> ret;
        ret.emplace_back();
        ret.back().emplace_back(sortedIntrvls.front()[0]);
        ret.back().emplace_back(sortedIntrvls.front()[1]);

        while (rht != sortedIntrvls.end()) {
            if (ret.back()[1] >= (*rht)[0])
                ret.back()[1] = std::max((*rht)[1], ret.back()[1]);
            else {
                ret.emplace_back();
                ret.back().emplace_back((*rht)[0]);
                ret.back().emplace_back((*rht)[1]);
            }
            ++rht;
        }

        return ret;
    }
};

#include <shared/dummy_main.inl>
