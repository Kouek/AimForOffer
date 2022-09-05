#include <iostream>

#include <array>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.size() == 0)
            return nullptr;
        stack<TreeNode *> leftPath;
        TreeNode *root = nullptr;
        leftPath.emplace(root = new TreeNode(preorder.front()));
        size_t eofLftPathIdx = 0;
        for (size_t preIdx = 1; preIdx < preorder.size(); ++preIdx) {
            auto curr = leftPath.top();
            if (curr->val != inorder[eofLftPathIdx]) {
                curr->left = new TreeNode(preorder[preIdx]);
                leftPath.emplace(curr->left);
            } else {
                while (!leftPath.empty() &&
                       leftPath.top()->val == inorder[eofLftPathIdx]) {
                    curr = leftPath.top();
                    leftPath.pop();
                    ++eofLftPathIdx;
                }
                curr->right = new TreeNode(preorder[preIdx]);
                leftPath.emplace(curr->right);
            }
        }
        return root;
    }
};

int main() {
    Solution solution;
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};

    // show left path
    auto root = solution.buildTree(preorder, inorder);
    queue<TreeNode *> que;
    que.emplace(root);
    while (!que.empty()) {
        auto curr = que.front();
        que.pop();
        if (curr) {
            que.emplace(curr->left);
            que.emplace(curr->right);
            cout << curr->val << ',';
        } else
            cout << "null,";
    }
    return 0;
}
