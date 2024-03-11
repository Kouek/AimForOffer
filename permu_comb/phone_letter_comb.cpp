#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 */

class Solution {
  private:
    static constexpr std::array<std::string_view, 10> PhoneNum2Chars = {"",    "",    "abc",  "def", "ghi",
                                                    "jkl", "mno", "pqrs", "tuv", "wxyz"};

  public:
    std::vector<std::string> letterCombinations(std::string digits) {
        if (digits.empty())
            return {};

        std::vector<std::string> ret;
        std::string ans;
        auto choose = [&](auto &&recur, int layer) {
            if (layer == digits.size()) {
                ret.emplace_back(ans);
                return;
            }

            auto &Chars = PhoneNum2Chars[digits[layer] - '0'];
            for (uint8_t i = 0; i < Chars.size(); ++i) {
                ans.push_back(Chars[i]);
                recur(recur, layer + 1);
                ans.erase(ans.size() - 1, 1);
            }
        };
        choose(choose, 0);
        
        return ret;
    }
};

#include <shared/dummy_main.inl>
