#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/longest-palindromic-substring/
 */

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
#ifdef NAIVE
        /*DP method:
         * p(l,r) = p(l+1,r-1) && s[l]==s[r]
         * with corner case:
         * p(i,i) = true,
         * p(i,i+1) = s[i]==s[i+1]
         */
        /*DP storage:
         * +------------> l
         * | _
         * | 0 _
         * | 0 0 _
         * | 0 0 0 _
         *\|/...
         * r 0 0 0 ... 0 _
         */
        std::vector<bool> dp(s.size() * (s.size() - 1) / 2, 0);

        auto get = [&](int l, int r) -> bool {
            if (l >= r)
                return true;
            return dp[(r - 1) * r / 2 + l];
        };
        auto set = [&](int l, int r) { dp[(r - 1) * r / 2 + l] = true; };

        std::array<int, 2> longestLR = {0, 0};
        for (int len = 2; len <= s.size(); ++len) {
            for (int r = len - 1; r < s.size(); ++r) {
                auto l = r + 1 - len;
                if (s[l] == s[r] && get(l + 1, r - 1)) {
                    set(l, r);
                    longestLR[0] = l;
                    longestLR[1] = r;
                }
            }
        }

        return s.substr(longestLR[0], longestLR[1] - longestLR[0] + 1);
#else
        std::array<int, 2> longestLR = {0, 0};
        auto expandFrom = [&](int l, int r) {
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                --l;
                ++r;
            }
            ++l;
            --r;

            if (r - l > longestLR[1] - longestLR[0]) {
                longestLR[0] = l;
                longestLR[1] = r;
            }
        };

        for (int i = 0; i < s.size(); ++i) {
            expandFrom(i, i);
            expandFrom(i, i + 1);
        }

        return s.substr(longestLR[0], longestLR[1] - longestLR[0] + 1);
#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
