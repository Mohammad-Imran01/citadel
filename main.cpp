#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <unordered_set>
#include <unordered_map>

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

    int longestSubstringWithoutRepCharBForce(string s)
    {
        int maxSize = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            unordered_set<char> st;
            for (int j = i; j < s.size() && (st.count(s[j]) == 0); ++j)
                st.insert(s[j]);
            maxSize = max(maxSize, (int)st.size());
        }
        return maxSize;
    }

    int longestSubstringWithoutRepChar(string s)
    {
        int maxSize = 0;
        unordered_set<char> st;
        for (int i = 0, j = 0; i < s.size() && j < s.size(); ++j)
        {
            while (st.count(s[j]) && i < j)
            {
                st.erase(s[i++]);
            }
            st.insert(s[j]);
            maxSize = max(maxSize, j - i + 1);
        }
        return maxSize;
    }
    vector<int> twoSum(vector<int> arr, int target)
    {
        unordered_map<int, int> mp;
        for (int ind = 0; ind < arr.size(); ++ind)
        {
            int key = target - arr[ind];
            if (mp.count(key))
                return {ind, mp[key]};
        }
        return {-1, -1};
    }
}

int main()
{
    Im::print<string>({"Hello,", "World!"});
}