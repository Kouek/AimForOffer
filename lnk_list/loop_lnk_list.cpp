#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/longest-common-prefix/
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next)
            return nullptr;

        auto slow = head;
        auto fast = head;
        while (true) {
            if (!fast || !fast->next)
                return nullptr;
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                break;
        }
        
        // slow-|a|->x-|b|->fast
        // fast-|a|->x-n*|b+c|+b->slow
        // =< a+n(b+c)+b = 2(a+b)
        // => a = (n-1)b+nc = (n-1)(b+c)+c
        auto ret = head;
        while (ret != slow) {
            ret = ret->next;
            slow = slow->next;
        }
        return ret;
    }
};

#include <shared/dummy_main.inl>
