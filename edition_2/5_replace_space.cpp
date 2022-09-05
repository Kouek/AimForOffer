#include <iostream>

#include <array>
#include <cassert>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    string replaceSpace(string s) {
        std::vector<size_t> spacePoss;
        for (size_t idx = 0; idx < s.size(); ++idx)
            if (s[idx] == ' ')
                spacePoss.emplace_back(idx);
        if (spacePoss.empty())
            return s;
        size_t spsIdx = spacePoss.size() - 1;
        size_t sIdx = s.size() - 1;
        static constexpr auto DLT_LEN = 2;
        s.resize(DLT_LEN * spacePoss.size() + s.size());
        for (; ; --sIdx)
            if (sIdx > spacePoss[spsIdx])
                s[sIdx + DLT_LEN * (1 + spsIdx)] = s[sIdx];
            else if (sIdx == spacePoss[spsIdx]) {
                s.replace(sIdx + DLT_LEN * spsIdx, 3, "%20");
                if (spsIdx == 0)
                    break;
                --spsIdx;
            }
        return s;
    }
};

int main() {
    Solution solution;
    string s = "We are happy.";
    s = "  ";
    auto ret = solution.replaceSpace(s);
    cout << ret;
    return 0;
}
