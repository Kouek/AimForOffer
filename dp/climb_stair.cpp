#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/climbing-stairs/
 */

class Solution {
  public:
    int climbStairs(int n) {
        // N[ni] = N[ni-1] + N[ni-2]
        if (n == 1)
            return 1;

        std::vector<int> ways(n, 0);
        ways[0] = 1;
        ways[1] = 2;

        for (int ni = 2; ni < n; ++ni)
            ways[ni] = ways[ni - 1] + ways[ni - 2];
        return ways.back();
    }
};

#include <shared/dummy_main.inl>
