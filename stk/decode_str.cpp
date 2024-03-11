#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/decode-string/
 */

class Solution {
  public:
    std::string decodeString(std::string s) {
        #define NAIVE
        std::stack<std::tuple<int,int>> stk;
        std::string ret;

        int cnt = 0;
        for (auto ch : s) {
            if (std::isdigit(ch)) {
                cnt = cnt * 10 + (ch - '0');
            } else if (ch == '[') {
                stk.emplace(cnt, ret.size());
                cnt = 0;
            } else if (std::isalpha(ch)) {
                ret.push_back(ch);
            } else {
                auto [cnt, prevEnd] = stk.top();
                auto len = ret.size() - prevEnd;
                for (int i = 0; i < cnt - 1; ++i)
                    for (int j = 0; j < len; ++j)
                        ret.push_back(ret[ret.size() - len]);
                stk.pop();
            }
        }

        return ret;
    }
};

//#include <shared/dummy_main.inl>

int main() { Solution().decodeString("3[a]2[bc]"); }
