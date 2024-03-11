#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/rotate-image/
 */

class Solution {
  public:
    void rotate(std::vector<std::vector<int>> &matrix) {
        /*(r,c)
         * -> (c,n-1-r)
         * -> (n-1-r,n-1-c)
         * -> (n-1-c,r)
         */

        int n = matrix.size();
        for (int r = 0; r < n / 2; ++r)
            for (int c = 0; c < (n + 1) / 2; ++c) {
                auto tmp = matrix[n - 1 - c][r];
                matrix[n - 1 - c][r] = matrix[n - 1 - r][n - 1 - c];
                matrix[n - 1 - r][n - 1 - c] = matrix[c][n - 1 - r];
                matrix[c][n - 1 - r] = matrix[r][c];
                matrix[r][c] = tmp;
            }
    }
};

#include <shared/dummy_main.inl>
