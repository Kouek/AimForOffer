#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/product-of-array-except-self/
 */

class Solution {
  public:
    std::vector<int> productExceptSelf(std::vector<int> &nums) {
#ifdef NAIVE
        std::vector<int> prefixProd;
        prefixProd.reserve(nums.size());
        prefixProd.emplace_back(nums.front());
        for (size_t i = 1; i < nums.size(); ++i)
            prefixProd.emplace_back(prefixProd[i - 1] * nums[i]);

        std::vector<int> postfixProd;
        postfixProd.reserve(nums.size());
        postfixProd.emplace_back(nums.back());
        for (size_t i = 1; i < nums.size(); ++i)
            postfixProd.emplace_back(postfixProd[i - 1] * nums[nums.size() - 1 - i]);

        std::vector<int> ret;
        ret.reserve(nums.size());
        ret.emplace_back(postfixProd[nums.size() - 2]);
        for (size_t i = 1; i < nums.size() - 1; ++i)
            ret.emplace_back(prefixProd[i - 1] * postfixProd[nums.size() - 2 - i]);
        ret.emplace_back(prefixProd[nums.size() - 2]);

        return ret;
#else
        std::vector<int> ret;
        ret.reserve(nums.size());
        ret.emplace_back(1);
        for (size_t i = 1; i < nums.size(); ++i)
            ret.emplace_back(ret[i - 1] * nums[i - 1]);

        int postfixProd = 1;
        for (size_t i = 0; i < nums.size(); ++i) {
            ret[nums.size() - 1 - i] *= postfixProd;
            postfixProd *= nums[nums.size() - 1 - i];
        }

        return ret;

#endif // NAIVE
    }
};

#include <shared/dummy_main.inl>
