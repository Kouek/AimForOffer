#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    bool exist(vector<vector<char>> &board, string word) {
        if (board.empty() || board.front().empty())
            return false;
        static constexpr std::array NEAR_RGN_CODES{0x01, 0x10, 0x12, 0x21};
        std::array num2 = {board.size(), board.front().size()};
        std::vector<std::vector<bool>> visiteds(num2[0]);
        for (auto &rowVec : visiteds)
            rowVec.resize(num2[1], false);
        stack<std::array<size_t, 3>> stk;

        for (size_t row = 0; row < num2[0]; ++row)
            for (size_t col = 0; col < num2[1]; ++col) {
                // start from (row, col)
                if (board[row][col] != word[0])
                    continue;

                stk.emplace(std::array<size_t, 3>{row, col, 0});
                visiteds[row][col] = true;

                while (!stk.empty()) {
                    auto &curr = stk.top();
                    if (stk.size() == word.size())
                        return true;

                    if (curr[2] == NEAR_RGN_CODES.size()) {
                        stk.pop();
                        visiteds[curr[0]][curr[1]] = false;
                    } else {
                        std::array<size_t, 3> next{0, 0, 0};
                        auto code = NEAR_RGN_CODES[curr[2]++];
                        for (uint8_t rc = 0; rc < 2; ++rc) {
                            switch ((code >> (rc << 2)) & 0xf) {
                            case 0x0:
                                if (curr[rc] == 0)
                                    next[rc] =
                                        std::numeric_limits<size_t>::max();
                                else
                                    next[rc] = curr[rc] - 1;
                                break;
                            case 0x1:
                                next[rc] = curr[rc];
                                break;
                            case 0x2:
                                if (curr[rc] == num2[rc] - 1)
                                    next[rc] =
                                        std::numeric_limits<size_t>::max();
                                else
                                    next[rc] = curr[rc] + 1;
                                break;
                            }
                        }
                        if (next[0] == std::numeric_limits<size_t>::max() ||
                            next[1] == std::numeric_limits<size_t>::max() ||
                            visiteds[next[0]][next[1]] == true)
                            continue;
                        if (board[next[0]][next[1]] == word[stk.size()]) {
                            stk.emplace(next);
                            visiteds[next[0]][next[1]] = true;
                        }
                    }
                }
            }
        return false;
    }
};

int main() {
    /*vector<vector<char>> board{
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    auto word = "ABCCED";*/
    vector<vector<char>> board{
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'E', 'S'}, {'A', 'D', 'E', 'E'}};
    auto word = "ABCESEEEFS";
    cout << Solution().exist(board, word);
}
