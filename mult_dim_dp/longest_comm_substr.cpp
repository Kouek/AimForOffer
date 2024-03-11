#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/longest-common-subsequence/
 */

class Solution {
  public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        // dp[i,j] = (dp[i-1, j-1] + 1) when test[i] == test[j]
        // dp[i,j] = (max(dp[i-1,j], dp[i, j-1])) when test[i] != test[j]
        auto len1 = text1.size();
        auto len2 = text2.size();

        std::array<std::vector<int>, 2> dp;
        dp[0].assign(len2, 0);
        dp[1].assign(len2, 0);

        for (int j = 0; j < len2; ++j) {
            dp[0][j] = text1[0] == text2[j] ? 1 : 0;
            dp[0][j] = std::max(dp[0][j], j >= 1 ? dp[0][j - 1] : 0);
        }

        uint8_t currIdx = 1;
        for (int i = 1; i < len1; ++i) {
            auto prevIdx = (currIdx + 1) % 2;
            dp[currIdx][0] = text1[i] == text2[0] ? 1 : 0;
            dp[currIdx][0] = std::max(dp[prevIdx][0], dp[currIdx][0]);

            for (int j = 1; j < len2; ++j) {
                if (text1[i] == text2[j])
                    dp[currIdx][j] = dp[prevIdx][j - 1] + 1;
                else
                    dp[currIdx][j] = std::max(dp[prevIdx][j], dp[currIdx][j - 1]);
            }

            currIdx = prevIdx;
        }

        return dp[(currIdx + 1) % 2].back();
    }
};

// #include <shared/dummy_main.inl>

int main() { Solution().longestCommonSubsequence("abcde", "abc"); }
