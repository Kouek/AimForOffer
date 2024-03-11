#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/word-break/
 */

class Solution {
  public:
    bool wordBreak(std::string s, std::vector<std::string> &wordDict) {
        // dp[i] =#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/perfect-squares/
 */

class Solution {
  public:
    int numSquares(int n) {
        // f[i] = min(1 + for j in [1,sqrt(i)]: f[i-j^2] )

        std::vector<int> nums(n + 1, std::numeric_limits<int>::max());
        nums[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::sqrt(i); ++j) {
                auto k = i - j * j;
                if (nums[i] > nums[k])
                    nums[i] = nums[k];
            }
            nums[i] += 1;
        }

        return nums.back();
    }
};

#include <shared/dummy_main.inl>
 or{ for word in words: dp[i-word.len] && s[i-word.len...i-1] == word }
        std::vector<bool> possibles(s.size() + 1, false);

        auto match = [&](int lft, int end, const std::string &word) {
            for (int i = 0; i < end - lft; ++i)
                if (s[lft + i] != word[i])
                    return false;
            return true;
        };

        possibles[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (auto &word : wordDict) {
                if (word.size() > i)
                    continue;
                auto j = i - word.size();
                possibles[i] = possibles[j] && match(j, i, word);
                if (possibles[i])
                    break;
            }
        }

        return possibles.back();
    }
};

#include <shared/dummy_main.inl>
