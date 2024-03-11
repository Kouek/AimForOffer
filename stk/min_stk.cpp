#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/perfect-squares/
 */

class Solution {
  public:
    int numSquares(int n) {
        // f[i] = min( for j in [0,sqrt(i)]: f[i-j*j] + 1 )

        std::vector<int> dp(n + 1, std::numeric_limits<int>::max());
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int jMax = std::sqrt(i);
            for (int j = 1; j <= jMax; ++j) {
                auto k = i - j * j;
                dp[i] = std::min(dp[k] + 1, dp[i]);
            }
        }

        return dp.back();
    }
};

#include <shared/dummy_main.inl>
