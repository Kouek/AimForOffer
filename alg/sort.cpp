#include <shared/all_stl.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *SortList(ListNode *head) {
    if (!head)
        return nullptr;
    if (!head->next)
        return head;

    auto moveNext = [](ListNode *&node) { node = node->next; };
    auto emptyNext = [moveNext](ListNode *&node) {
        auto *tmp = node;
        moveNext(node);
        tmp->next = nullptr;
    };
    auto merge = [moveNext](ListNode *lft, ListNode *rht) -> std::array<ListNode *, 2> {
        ListNode dummy(-1, lft);
        auto *prev = &dummy;
        while (lft && rht) {
            if (lft->val <= rht->val) {
                prev->next = lft;
                moveNext(lft);
                moveNext(prev);
            } else {
                prev->next = rht;
                moveNext(rht);
                moveNext(prev);
            }
        }
        while (lft) {
            prev->next = lft;
            moveNext(lft);
            moveNext(prev);
        }
        while (rht) {
            prev->next = rht;
            moveNext(rht);
            moveNext(prev);
        }
        prev->next = nullptr;

        return {dummy.next, prev};
    };

    int n = 0;
    auto *curr = head;
    while (curr) {
        ++n;
        moveNext(curr);
    }

    ListNode dummy(-1, head);
    for (int stride = 1; stride < n; stride *= 2) {
        auto *prev = &dummy;
        auto *lft = dummy.next;
        while (lft) {
            auto *rht = lft;
            for (int i = 1; i < stride && rht; ++i)
                moveNext(rht);
            if (rht)
                emptyNext(rht);

            auto *next = rht;
            for (int i = 1; i < stride && next; ++i)
                moveNext(next);
            if (next)
                emptyNext(next);

            auto [head, tail] = merge(lft, rht);
            prev->next = head;
            prev = tail;

            lft = next;
        }
    }

    return dummy.next;
}

class Tests {
  private:
    std::map<std::string, std::function<void(void)>> testFuncs;

  public:
    Tests() {
        testFuncs.emplace("Partial Sort Linked List", []() {
            auto list =
                new ListNode(4, new ListNode(2, new ListNode(1, new ListNode(3, new ListNode(0)))));
            list = SortList(list);

            auto *curr = list;
            while (curr) {
                std::cout << std::format("{}, ", curr->val);
                curr = curr->next;
            }

            curr = list;
            while (curr) {
                auto tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        });
    }

#define CONST_REF_GETTER(member, nameInFunc)                                                       \
    const decltype(member) &Get##nameInFunc() const { return member; }
    CONST_REF_GETTER(testFuncs, TestFunctions)
#undef CONST_REF_GETTER
};

int main() {
    Tests tests;
    int item = 0;
    for (auto &[name, _] : tests.GetTestFunctions()) {
        std::cout << std::format("{} -> {}\n", item, name);
        ++item;
    }

    std::cin >> item;
    int i = 0;
    for (auto &[_, func] : tests.GetTestFunctions()) {
        if (i == item) {
            func();
            break;
        }
        ++i;
    }
}
