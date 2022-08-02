#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
        int rowNum = matrix.size();
        if (rowNum == 0)
            return false;
        int colNum = matrix[0].size();
        if (colNum == 0)
            return false;

        int rowS, rowE;
        for (rowS = 0; rowS < rowNum; ++rowS)
            if (matrix[rowS][colNum - 1] >= target)
                break;
        for (rowE = rowNum - 1; rowE > 0; --rowE)
            if (matrix[rowE][0] <= target)
                break;
        int colS, colE;
        for (colS = 0; colS < colNum; ++colS)
            if (matrix[rowNum - 1][colS] >= target)
                break;
        for (colE = colNum - 1; colE > 0; --colE)
            if (matrix[0][colE] <= target)
                break;
        for (int row = rowS; row <= rowE; ++row)
            for (int col = colS; col <= colE; ++col)
                if (matrix[row][col] == target)
                    return true;
        return false;
    }
};

class SolutionBST {
  public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
        // TODO
    }
};

int main() {
    vector<vector<int>> mat{{1, 4, 7, 11, 15},
                            {2, 5, 8, 12, 19},
                            {3, 6, 9, 16, 22},
                            {10, 13, 14, 17, 24},
                            {18, 21, 23, 26, 30}};
    SolutionBST solution;
    cout << solution.findNumberIn2DArray(mat, 32);
}
