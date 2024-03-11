#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/longest-common-prefix/
 */

class Solution {
  public:
    std::string longestCommonPrefix(std::vector<std::string> &strs) {
        for (auto &str : strs)
            if (str.empty())
                return "";

        std::string ret;
        int col = 0;
        while (true) {
            auto ch = strs[0][col];
            auto canCont = col + 1 < strs[0].size();

            for (int row = 1; row < strs.size(); ++row) {
                if (strs[row][col] != ch) {
                    canCont = false;
                    return ret;
                }

                if (col + 1 == strs[row].size())
                    canCont = false;
            }

            ret.push_back(ch);
            if (!canCont)
                break;
            ++col;
        }

        return ret;
    }
};

#include <shared/dummy_main.inl>
