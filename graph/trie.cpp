#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/implement-trie-prefix-tree/
 */

class Trie {
  private:
    struct Node {
        bool isEnd;
        std::array<Node *, 26> chs;

        Node() : isEnd(false), chs({nullptr}) {}
    };
    Node root;

  public:
    Trie() {}

    void insert(std::string word) {
        auto par = &root;
        auto append = [&](char ch) {
            auto &chEntry = par->chs[ch - 'a'];
            if (!chEntry)
                chEntry = new Node;
            par = chEntry;
        };

        for (auto ch : word)
            append(ch);
        par->isEnd = true;
    }

    bool search(std::string word) {
        auto par = &root;
        for (auto ch : word) {
            auto chEntry = par->chs[ch - 'a'];
            if (!chEntry)
                return false;
            par = chEntry;
        }

        return par->isEnd;
    }

    bool startsWith(std::string prefix) {
        auto par = &root;
        for (auto ch : prefix) {
            auto chEntry = par->chs[ch - 'a'];
            if (!chEntry)
                return false;
            par = chEntry;
        }

        return true;
    }
};

#include <shared/dummy_main.inl>
