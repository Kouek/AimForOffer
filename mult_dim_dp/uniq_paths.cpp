#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/unique-paths/
 */

class Solution {
  public:
    int uniquePaths(int m, int n) {
#ifdef NAIVE
        std::vector<bool> visits(m * n, false);
        auto map = [&](int r, int c) { return r * n + c; };

        std::stack<std::tuple<int, int, int>> stk;
        stk.emplace(0, 0, 0);
        int cnt = 0;
        while (!stk.empty()) {
            auto &[r, c, s] = stk.top();
            if (r == m - 1 && c == n - 1) {
                ++cnt;
                stk.pop();
                continue;
            }
            visits[map(r, c)] = true;

            if (s == 2) {
                stk.pop();
                visits[map(r, c)] = false;
                continue;
            }

            int nr = r, nc = c;
            if (s == 0)
                nc = c + 1;
            else if (s == 1)
                nr = r + 1;

            ++s;
            if (nr < m && nc < n && !visits[map(nr, nc)])
                stk.emplace(nr, nc, 0);
        }

        return cnt;
#else
        // f[i,j] = f[i-1,j] + f[i,j-1]
        std::array<std::vector<int>, 2> dp;
        dp[0].assign(n, 0);
        dp[1].assign(n, 0);
        for (int j = 0; j < n; ++j)
            dp[0][j] = 1;

        uint8_t currIdx = 1;
        for (int i = 1; i < m; ++i) {
            auto prevIdx = (currIdx + 1) % 2;

            dp[currIdx][0] = dp[prevIdx][0];
            for (int j = 1; j < n; ++j)
                dp[currIdx][j] = dp[currIdx][j - 1] + dp[prevIdx][j];
            currIdx = prevIdx;
        }

        return dp[(currIdx + 1) % 2][n - 1];
#endif
    }
};

// #include <shared/dummy_main.inl>

int main() { Solution().uniquePaths(3, 2); }
