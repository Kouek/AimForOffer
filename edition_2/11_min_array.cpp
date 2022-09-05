#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    int minArray(vector<int> &numbers) {
        size_t lft = 0, rht = numbers.size() - 1;
        while (lft < rht) {
            auto mid = (lft + rht) >> 1;
            if (numbers[mid] < numbers[rht])
                rht = mid;
            else if (numbers[mid] > numbers[rht])
                lft = mid + 1;
            else
                --rht;
        }
        return numbers[lft];
    }
};

int main() { 
    //vector<int> nums{2, 2, 2, 0, 1};
    //vector<int> nums{3, 4, 5, 1, 2};
    vector<int> nums{2, 2, 0, 2};
    Solution solution;
    cout << solution.minArray(nums);

    return 0; }
