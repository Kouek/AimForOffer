#include <iostream>

#include <array>
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
        // TODO
    }
};

int main() { 
    Solution solution;
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};

    // show left path
    auto root = solution.buildTree(preorder, inorder);
    auto curr = root;
    while (curr) {
        cout << curr->val << ' ';
        curr = curr->left;
    }
    return 0;
}
