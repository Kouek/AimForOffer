#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/sqrtx/solutions/
 */

class Solution {
  public:
    int mySqrt(int x) {
#ifdef NAIVE
        int l = 0, r = x;
        int ans = 0;
        while (l <= r) {
            long mid = (l + r) / 2;
            if (mid * mid <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
#else
        // f(x) = x^2 - C
        // f'(x) = 2x
        // (x0,f(x0)) with tangent 2x0 => 2x0 (x - x0) = y - f(x0)
        // y = 2x0x - 2x0^2 + f(x0)
        // let y = 0 => x = x0 - f(x0)/(2x0) = x0 - (x0^2 - C)/(2x0)
        // = x0 * 0.5 + C/(2x0)

        double x0 = x;
        while (true) {
            auto newX0 = .5 * (x0 + x / x0);
            if (abs(newX0 - x0) <= 1e-7)
                break;
        }
        return x0;

#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
