#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/set-matrix-zeroes/
 */

class Solution {
  public:
    void setZeroes(std::vector<std::vector<int>> &matrix) {
#ifdef NAIVE
        auto rowNum = matrix.size();
        auto colNum = matrix.front().size();
        std::vector<bool> zeroRow(rowNum, false);
        std::vector<bool> zeroCol(colNum, false);

        for (int r = 0; r < rowNum; ++r)
            for (int c = 0; c < colNum; ++c)
                if (matrix[r][c] == 0) {
                    zeroRow[r] = true;
                    zeroCol[c] = true;
                }

        for (int r = 0; r < rowNum; ++r)
            if (zeroRow[r])
                for (int c = 0; c < colNum; ++c)
                    matrix[r][c] = 0;

        for (int c = 0; c < colNum; ++c)
            if (zeroCol[c])
                for (int r = 0; r < rowNum; ++r)
                    matrix[r][c] = 0;
#else
        auto rowNum = matrix.size();
        auto colNum = matrix.front().size();

        auto row0Has0 = false;
        for (int c = 0; c < colNum; ++c)
            if (matrix[0][c] == 0) {
                row0Has0 = true;
                break;
            }

        auto col0Has0 = false;
        for (int r = 0; r < rowNum; ++r)
            if (matrix[r][0] == 0) {
                col0Has0 = true;
                break;
            }

        for (int r = 1; r < rowNum; ++r)
            for (int c = 1; c < colNum; ++c)
                if (matrix[r][c] == 0)
                    matrix[0][c] = matrix[r][0] = 0;
        for (int c = 1; c < colNum; ++c)
            if (matrix[0][c] == 0)
                for (int r = 1; r < rowNum; ++r)
                    matrix[r][c] = 0;
        for (int r = 1; r < rowNum; ++r)
            if (matrix[r][0] == 0)
                for (int c = 1; c < colNum; ++c)
                    matrix[r][c] = 0;

        if (row0Has0)
            for (int c = 0; c < colNum; ++c)
                matrix[0][c] = 0;
        if (col0Has0)
            for (int r = 0; r < rowNum; ++r)
                matrix[r][0] = 0;
#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
