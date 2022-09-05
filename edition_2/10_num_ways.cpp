#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    int numWays(int n) {
        if (n <= 1)
            return 1;
        std::array<int, 3> nums;
        nums[1] = nums[0] = 1;
        for (int i = 2; i <= n; ++i) {
            nums[2] = (nums[0] + nums[1]) % 1000000007;
            nums[0] = nums[1];
            nums[1] = nums[2];
        }
        return nums[2];
    }
};

int main() {
    int n = 0;
    cin >> n;
    cout << Solution().numWays(n);
    return 0;
}
