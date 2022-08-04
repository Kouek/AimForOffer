#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    string replaceSpace(string s) {
        string ret;
        {
            size_t spcCnt = 0;
            for (const auto &ch : s)
                if (ch == ' ')
                    ++spcCnt;
            // reserve for "%20"
            ret.reserve(s.size() + spcCnt * 2);
        }

        for (auto sItr = s.begin(); sItr != s.end(); ++sItr)
            if (*sItr == ' ')
                ret.append("%20");
            else
                ret.append(1, *sItr);
        return ret;
    }
};

int main() {
    Solution solution;
    string s = "We are happy.";
    auto ret = solution.replaceSpace(s);
    cout << ret;
    return 0;
}
