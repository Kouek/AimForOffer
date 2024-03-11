#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/binary-tree-right-side-view/
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
    std::vector<int> rightSideView(TreeNode *root) {
        if (!root)
            return {};

        std::queue<TreeNode *> q;
        q.emplace(root);

        std::vector<int> ret;
        while (!q.empty()) {
            auto popCnt = q.size();
            auto enQue = [&]() {
                auto top = q.front();
                if (top->left)
                    q.emplace(top->left);
                if (top->right)
                    q.emplace(top->right);

                q.pop();
                --popCnt;
            };
            while (popCnt != 1)
                enQue();
            ret.emplace_back(q.front()->val);
            enQue();
        }

        return ret;
    }
};

#include <shared/dummy_main.inl>
