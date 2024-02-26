#include "shared/all_stl.h"

/*URL:
* https://leetcode.cn/problems/3sum/
*/

class Solution {
  public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        std::vector<std::vector<int>> ret;

        std::vector<int> sortedNums(nums);
        std::sort(sortedNums.begin(), sortedNums.end());

        // Assume a + b + c = 0 with a <= 0 and c >= 0
        for (auto ia = sortedNums.begin(); ia != sortedNums.end() && *ia <= 0; ++ia) {
            if (ia != sortedNums.begin() && *ia == *(ia - 1))
                continue;

            auto b_add_c = -*ia;
            auto ic = sortedNums.end() - 1;

            for (auto ib = ia + 1; ib != sortedNums.end(); ++ib) {
                if (ib != ia + 1 && *ib == *(ib - 1))
                    continue;

                while (ib < ic && (*ib + *ic > b_add_c))
                    --ic;
                if (ib == ic)
                    break; // reach -a < 2*b => b > 0 => no need to move

                if (*ib + *ic == b_add_c)
                    ret.push_back({*ia, *ib, *ic});
            }
        }

        return ret;
    }
};

#include "shared/dummy_main.inl"
