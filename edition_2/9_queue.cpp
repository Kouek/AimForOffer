#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class CQueue {
  private:
    stack<int> head, tail;

  public:
    CQueue() {}

    void appendTail(int value) { tail.emplace(value);
    }

    int deleteHead() {
        if (head.empty()) {
            if (tail.empty())
                return -1;
            while (tail.size() != 1) {
                head.emplace(tail.top());
                tail.pop();
            }
            int ret = tail.top();
            tail.pop();
            return ret;
        }
        int ret = head.top();
        head.pop();
        return ret;
    }
};

int main() {
    CQueue* obj = new CQueue();
    vector<int> vals{0, 1, 2, 3, 4, 5};
    for (auto val : vals)
        obj->appendTail(val);
    for (auto val : vals) {
        auto ret = obj->deleteHead();
        cout << ret << ',';
    }
}
