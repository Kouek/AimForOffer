#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/number-of-islands/
 */

class Solution {
  public:
    int numIslands(std::vector<std::vector<char>> &grid) {
        using Grid = std::array<int, 2>;

        auto colNum = grid.front().size();

        std::vector<bool> visits(grid.size() * grid.front().size(), false);
        auto check = [&](const Grid &coord) {
            auto [r, c] = coord;
            return r >= 0 && r < grid.size() && c >= 0 && c < grid.front().size() &&
                   grid[r][c] != '0' && !visits[r * colNum + c];
        };

        std::queue<Grid> q;
        int ret = 0;
        Grid start;
        for (start[0] = 0; start[0] < grid.size(); ++start[0])
            for (start[1] = 0; start[1] < grid.front().size(); ++start[1]) {
                if (!check(start))
                    continue;

                ++ret;
                q.push(start);
                while (!q.empty()) {
                    auto [r, c] = q.front();

                    Grid next = {r, c};
                    --next[0];
                    if (check(next)) {
                        q.push(next);
                        visits[next[0] * colNum + next[1]] = true;
                    }
                    next[0] += 2;
                    if (check(next)) {
                        q.push(next);
                        visits[next[0] * colNum + next[1]] = true;
                    }
                    --next[0];
                    --next[1];
                    if (check(next)) {
                        q.push(next);
                        visits[next[0] * colNum + next[1]] = true;
                    }
                    next[1] += 2;
                    if (check(next)) {
                        q.push(next);
                        visits[next[0] * colNum + next[1]] = true;
                    }

                    q.pop();
                }
            }

        return ret;
    }
};

#include <shared/dummy_main.inl>
