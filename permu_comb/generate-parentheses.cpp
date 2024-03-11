#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/generate-parentheses/
 */

class Solution {
  public:
    std::vector<std::string> generateParenthesis(int n) {
        if (n == 0)
            return {};

        std::vector<std::string> ret;
        std::string ans;
        auto gen = [&](auto &&recur, int lftNum, int rhtNum) {
            if (ans.size() == n * 2) {
                ret.emplace_back(ans);
                return;
            }

            if (lftNum < n) {
                ans.push_back('(');
                recur(recur, lftNum + 1, rhtNum);
                ans.pop_back();
            }

            if (rhtNum < lftNum) {
                ans.push_back(')');
                recur(recur, lftNum, rhtNum + 1);
                ans.pop_back();
            }
        };
        gen(gen, 0, n);

        return ret;
    }
};

#include <shared/dummy_main.inl>
