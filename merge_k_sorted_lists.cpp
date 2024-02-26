#include "shared/all_stl.h"

/*URL:
 * https://leetcode.cn/problems/merge-k-sorted-lists/
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        ListNode *ret = nullptr;
        auto prev = &ret;
        auto append = [&](int val) {
            if (!(*prev)) {
                *prev = new ListNode(val);
                return;
            }

            (*prev)->next = new ListNode(val);
            prev = &(*prev)->next;
        };

#ifdef NAIVE
        std::unordered_map<int, ListNode *> remains;
        remains.reserve(lists.size());
        for (auto itr = lists.begin(); itr != lists.end(); ++itr)
            remains.emplace(std::piecewise_construct,
                            std::forward_as_tuple(static_cast<int>(itr - lists.begin())),
                            std::forward_as_tuple(*itr));

        while (true) {
            auto minVal = std::numeric_limits<int>::max();
            auto minValItr = remains.end();
            auto itr = remains.begin();
            while (itr != remains.end()) {
                if (!itr->second) {
                    remains.erase(itr++);
                    continue;
                }

                if (minVal > itr->second->val) {
                    minVal = itr->second->val;
                    minValItr = itr;
                }
                ++itr;
            }

            if (remains.empty())
                break;

            append(minVal);
            minValItr->second = minValItr->second->next;
        }

#else
        auto cmp = [](ListNode *a, ListNode *b) { return a->val > b->val; };
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(cmp)> heap(cmp);

        for (auto head : lists)
            if (head)
                heap.emplace(head);
        while (!heap.empty()) {
            auto top = heap.top();
            append(top->val);
            heap.pop();
            if (top->next)
                heap.emplace(top->next);
        }
#endif // NAIVE

        return ret;
    }
};

//#include "shared/dummy_main.inl"

int main() {
    auto head0 = new ListNode(1, new ListNode(4, new ListNode(5)));
    auto head1 = new ListNode(1, new ListNode(3, new ListNode(4)));
    auto head2 = new ListNode(2, new ListNode(6));
    std::vector inputs = {head0, head1, head2};
    Solution().mergeKLists(inputs);

    return 0;
}
