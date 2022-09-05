#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    int hammingWeight(uint32_t n) {
        static constexpr auto MAP_HEX_TO_HAMMING_W = []() { 
        std::array<uint8_t, 16> ret{0};
            for (uint8_t hex = 0; hex < 16; ++hex)
                ret[hex] = ((hex & 0x1) ? 1 : 0) + ((hex & 0x2) ? 1 : 0) +
                           ((hex & 0x4) ? 1 : 0) + ((hex & 0x8) ? 1 : 0);
            return ret;
        }();
        int w = 0;
        for (uint8_t hexIdx = 0; hexIdx < 8; ++hexIdx) {
            w += MAP_HEX_TO_HAMMING_W[n & 0xf];
            n = n >> 4;
        }
        return w;
    }
};

int main() {
    Solution solution;
    cout << solution.hammingWeight(0xffffffff);
    return 0;
}