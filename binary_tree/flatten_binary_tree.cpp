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
    void flatten(TreeNode *root) {
#ifdef NAIVE
        if (!root)
            return;

        auto flatten = [&](auto&& recur, TreeNode* root) -> TreeNode* {
            auto processRootLeft = [&]() {
                root->right = root->left;
                root->left = nullptr;
            };

            if (root->left && root->right) {
                auto rht = root->right;
                processRootLeft();

                auto tail = recur(recur, root->right);
                tail->right = rht;
                return recur(recur, rht);
            } else if (root->left) {
                processRootLeft();
                return recur(recur, root->right);
            } else if (root->right)
                return recur(recur, root->right);

            return root;
        };
        flatten(flatten, root);
#else
        auto curr = root;
        while (curr) {
            auto next = curr->left;
            if (next) {
                auto predecessor = next;
                while (predecessor->right)
                    predecessor = predecessor->right;

                predecessor->right = curr->right;

                curr->right = next;
                curr->left = nullptr;
            }
            curr = curr->right;
        }
#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
