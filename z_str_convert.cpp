#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/zigzag-conversion/description/
 */

class Solution {
  public:
    std::string convert(std::string s, int numRows) {
        if (numRows == 0 || numRows == 1)
            return s;

        std::string ret;
        ret.reserve(s.size());

        auto totTimePeriod = 2 * numRows - 2;
        for (int row = 0; row < numRows; ++row) {
            std::array<int, 2> timePeriod = {totTimePeriod - row * 2, row * 2};

            auto i = row;
            int prevI = -1;
            uint8_t tpIdx = 0;
            while (i < s.size()) {
                if (prevI != i)
                    ret.append(1, s[i]);
                prevI = i;
                
                i += timePeriod[tpIdx];
                tpIdx = (tpIdx + 1) & 0b1;
            }
        }

        return ret;
    }
};

#include "shared/dummy_main.inl"
