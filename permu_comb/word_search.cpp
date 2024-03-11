#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/word-search/
 */

class Solution {
  public:
    bool exist(std::vector<std::vector<char>> &board, std::string word) {
        using Coord = std::array<int, 2>;
        std::stack<std::tuple<Coord, uint8_t>> stk;
        std::vector<bool> visits(board.size() * board.front().size(), false);

        int rowNum = board.size();
        int colNum = board.front().size();
        auto inRng = [&](const Coord &coord) {
            return coord[0] >= 0 && coord[0] < rowNum && coord[1] >= 0 && coord[1] < colNum;
        };
        auto isVisited = [&](const Coord &coord) { return visits[coord[0] * colNum + coord[1]]; };
        auto visit = [&](const Coord &coord) { visits[coord[0] * colNum + coord[1]] = true; };
        auto unvisit = [&](const Coord &coord) { visits[coord[0] * colNum + coord[1]] = false; };
        auto map = [&](const Coord &coord) -> char & { return board[coord[0]][coord[1]]; };

        Coord start;
        for (start[0] = 0; start[0] < rowNum; ++start[0])
            for (start[1] = 0; start[1] < colNum; ++start[1]) {
                if (map(start) != word[0])
                    continue;

                stk.emplace(start, 0);

                auto find = false;
                int wi = 1;
                visit(start);
                while (!stk.empty()) {
                    if (wi == word.size()) {
                        find = true;
                        break;
                    }

                    auto &[prev, state] = stk.top();
                    if (state == 4) {
                        unvisit(prev);
                        stk.pop();
                        --wi;
                        continue;
                    }
                    auto next = [&]() -> Coord {
                        switch (state) {
                        case 0:
                            return {prev[0] - 1, prev[1]};
                        case 1:
                            return {prev[0] + 1, prev[1]};
                        case 2:
                            return {prev[0], prev[1] - 1};
                        default:
                            return {prev[0], prev[1] + 1};
                        }
                    }();

                    if (inRng(next) && !isVisited(next) && map(next) == word[wi]) {
                        visit(next);
                        ++wi;
                        stk.emplace(next, 0);
                    }
                    ++state;
                }

                if (find) 
                    return true;
            }

        return false;
    }
};

#include <shared/dummy_main.inl>
