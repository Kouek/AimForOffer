#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/find-median-from-data-stream/
 */

class MedianFinder {
  private:
    size_t heapTotNum = 0;
    std::priority_queue<int> lessThanMedNums;
    std::priority_queue<int, std::vector<int>, std::greater<int>> greaterThanMedNums;

  public:
    MedianFinder() {}

    void addNum(int num) {
        if (lessThanMedNums.empty()) {
            lessThanMedNums.emplace(num);
            heapTotNum = 1;
            return;
        }

        if (num <= lessThanMedNums.top()) {
            lessThanMedNums.emplace(num);
            if (lessThanMedNums.size() > greaterThanMedNums.size() + 1) {
                greaterThanMedNums.emplace(lessThanMedNums.top());
                lessThanMedNums.pop();
            }
        } else {
            greaterThanMedNums.emplace(num);
            if (lessThanMedNums.size() < greaterThanMedNums.size()) {
                lessThanMedNums.emplace(greaterThanMedNums.top());
                greaterThanMedNums.pop();
            }
        }
        ++heapTotNum;
    }

    double findMedian() {
        if (heapTotNum % 2 == 0)
            return .5 * (lessThanMedNums.top() + greaterThanMedNums.top());
        return lessThanMedNums.top();
    }
};

#include <shared/dummy_main.inl>
