#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <set>

using namespace std;

namespace Im
{
    template <typename Type>
    void print(const vector<Type> &arr)
    {
        for (const auto &item : arr)
            cout << item << " ";
        cout << "\n";
    } // begining
    class LRUCache
    {
        int maxSize;
        list<int> usage;
        unordered_map<int, pair<int, list<int>::iterator>> cache;

    public:
        LRUCache(int capacity)
            : maxSize(capacity) {}

        int get(int key)
        {
            if (!cache.count(key))
                return -1;
            usage.erase(cache[key].second);
            usage.push_front(key);
            cache[key].second = usage.begin();
        }

        int insert(int key, int val)
        {
            if (cache.count(key))
            {
                usage.erase(cache[key].second);
            }
            else if (cache.size() == maxSize)
            {
                cache.erase(usage.back());
                usage.pop_back();
            }
            usage.push_front(key);
            cache[key] = {val, usage.begin()};
        }
    };
}

int main()
{
    Im::print<string>({"Hello,", "World!"});
}