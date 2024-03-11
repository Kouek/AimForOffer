#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/top-k-frequent-elements/
 */

class Solution {
  public:
    std::vector<int> topKFrequent(std::vector<int> &nums, int k) {
        if (nums.size() <= k)
            return nums;

        std::unordered_map<int, int> num2freqs;
        for (auto num : nums) {
            if (auto itr = num2freqs.find(num); itr != num2freqs.end())
                ++itr->second;
            else
                num2freqs.emplace(num, 1);
        }

        struct Freq {
            int freq;
            int num;

            bool operator<(const Freq &other) const { return num > other.num; }
        };
        std::priority_queue<Freq> topFreqs;
        for (auto &[num, freq] : num2freqs) {
            if (topFreqs.size() < k)
                topFreqs.emplace(freq, num);
            else if (freq > topFreqs.top().freq) {
                topFreqs.pop();
                topFreqs.emplace(freq, num);
            }
        }

        std::vector<int> ret;
        ret.reserve(k);
        while (!topFreqs.empty()) {
            ret.emplace_back(topFreqs.top().num);
            topFreqs.pop();
        }
        return ret;
    }
};

//#include <shared/dummy_main.inl>

int main() {
    std::vector a = {1, 1, 1, 2, 2, 3};
    Solution().topKFrequent(a, 2);
}
