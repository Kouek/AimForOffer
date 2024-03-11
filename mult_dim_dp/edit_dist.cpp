#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/edit-distance/
 */

class Solution {
  public:
    int minDistance(std::string word1, std::string word2) {
        // f[i,j] = min( f[i-1,j] + 1, f[i,j-1] + 1, f[i-1,j-1] + word1[i]==word2[j] ? 0 : 1 )

        auto len1 = word1.size();
        auto len2 = word2.size();

        if (len1 * len2 == 0)
            return len1 + len2;

        std::vector<unsigned int> dp((len1 + 1) * (len2 + 1),
                                     std::numeric_limits<unsigned int>::max());
        auto map = [&](int i, int j) -> unsigned int & { return dp[i * (len2 + 1) + j]; };

        for (int j = 0; j <= len2; ++j)
            map(0, j) = j;
        for (int i = 0; i <= len1; ++i)
            map(i, 0) = i;

        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                auto &x = map(i, j);
                x = std::min(x, map(i - 1, j) + 1);
                x = std::min(x, map(i, j - 1) + 1);
                x = std::min(x, map(i - 1, j - 1) + (word1[i - 1] == word2[j - 1] ? 0 : 1));
            }
        }

        return dp.back();
    }
};

// #include <shared/dummy_main.inl>

int main() { Solution().minDistance("sea", "eat"); }
