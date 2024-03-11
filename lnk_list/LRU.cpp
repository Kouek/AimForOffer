#include <shared/all_stl.h>

/*URL:
 * https://leetcode.cn/problems/lru-cache/
 */

class LRUCache {
  private:
    int cap;
    std::list<int> lruKeys;
    std::unordered_map<int, std::tuple<int, decltype(lruKeys)::iterator>> kvs;

  private:
    int& visit(decltype(kvs)::iterator itr) {
        auto &[val, lruItr] = itr->second;
        lruKeys.erase(lruItr);
        lruKeys.emplace_front(itr->first);
        lruItr = lruKeys.begin();

        return val;
    }

  public:
    LRUCache(int capacity) : cap(capacity) { kvs.reserve(capacity); }

    int get(int key) {
        auto itr = kvs.find(key);
        if (itr == kvs.end())
            return -1;

        return visit(itr);
    }

    void put(int key, int value) {
        auto itr = kvs.find(key);
        if (itr != kvs.end()) {
            visit(itr) = value;
            return;
        }

        if (kvs.size() == cap) {
            auto lastKey = lruKeys.back();
            lruKeys.pop_back();
            kvs.erase(lastKey);
        }

        lruKeys.emplace_front(key);
        kvs.emplace(std::piecewise_construct, std::forward_as_tuple(key),
                    std::forward_as_tuple(value, lruKeys.begin()));
    }
};

#include <shared/dummy_main.inl>
