#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/minimum-window-substring/
 */

class Solution {
  public:
    std::string minWindow(std::string s, std::string t) {
        /*distrib[lft,rht] = distrib[lft,rht-1] + distrib[rht,rht]
        * distrib[lft+1,rht] = distrib[lft,rht] - distrib[lft,lft]
        */

        if (s.size() < t.size())
            return "";

        auto map = [](char ch) -> int {
            if (ch >= 'a')
                return 26 + ch - 'a';
            return ch - 'A';
        };

        std::array<uint32_t, 26 * 2> tDistrb = {0};
        for (auto ch : t)
            ++tDistrb[map(ch)];

        auto lft = s.begin();
        auto rht = s.begin();
        std::array<uint32_t, 26 * 2> sDistrb = {0};
        std::string ret;

        auto match = false;
        ++sDistrb[map(*rht)];
        while (true) {
            auto currMatch = [&]() {
                for (uint8_t i = 0; i < tDistrb.size(); ++i)
                    if (sDistrb[i] < tDistrb[i])
                        return false;
                return true;
            }();

            if (match && !currMatch && (ret.empty() || ret.size() > (rht - lft + 2)))
                ret.assign(lft - 1, rht + 1);

            match = currMatch;
            if (!match) {
                ++rht;
                if (rht == s.end())
                    break;
                ++sDistrb[map(*rht)];
            } else {
                --sDistrb[map(*lft)];
                ++lft;
            }
        }

        return ret;
    }
};

#include "shared/dummy_main.inl"
