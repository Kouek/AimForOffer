#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/pascals-triangle/
 */

class Solution {
  public:
    std::vector<std::vector<int>> generate(int numRows) {
        // 0:        [0]
        // 1:      [0] [1]
        // 2:    [0] [1] [2]
        // 3:  [0] [1] [2] [3]
        // 4:[0] [1] [2] [3] [4]
        std::vector<std::vector<int>> ret(numRows);
        ret[0].emplace_back(1);

        for (int row = 1; row < numRows; ++row) {
            auto &prevColVec = ret[row - 1];
            auto &colVec = ret[row];
            auto numCol = row + 1;
            
            colVec.resize(numCol);
            colVec[0] = colVec[numCol - 1] = 1;
            for (int col = 1; col < numCol - 1; ++col)
                colVec[col] = prevColVec[col - 1] + prevColVec[col];
        }

        return ret;
    }
};

#include <shared/dummy_main.inl>
