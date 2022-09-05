#include <iostream>

#include <array>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        double x_contribute = x;
        while (N > 0) {
            if (N % 2 == 1)
                ans *= x_contribute;
            x_contribute *= x_contribute;
            N /= 2;
        }
        return ans;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};

int main() {
    Solution solution;
    cout << solution.myPow(2, -5) << endl;
    cout << solution.myPow(0.00001, 2147483647) << endl;
    return 0;
}
