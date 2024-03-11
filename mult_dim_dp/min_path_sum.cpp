#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/unique-paths/
 */

class Solution {
  public:
    int minPathSum(std::vector<std::vector<int>> &grid) {
        auto rowNum = grid.size();
        auto colNum = grid.front().size();
        std::array<std::vector<unsigned>, 2> dp;
        dp[0].assign(colNum, std::numeric_limits<unsigned>::max());
        dp[1].assign(colNum, std::numeric_limits<unsigned>::max());

        dp[0][0] = grid[0][0];
        for (int j = 1; j < colNum; ++j)
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        uint8_t currIdx = 1;
        for (int i = 1; i < rowNum; ++i) {
            auto prevIdx = (currIdx + 1) % 2;

            dp[currIdx][0] = dp[prevIdx][0] + grid[i][0];
            for (int j = 1; j < colNum; ++j)
                dp[currIdx][j] = std::min(dp[currIdx][j - 1], dp[prevIdx][j]) + grid[i][j];

            currIdx = prevIdx;
        }

        return dp[(currIdx + 1) % 2].back();
    }
};

#include <shared/dummy_main.inl>
