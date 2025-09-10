#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <utility>
#include <memory>
#include <algorithm>
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

    // two unqiue indices num whose sum is given target.
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

    // all unique combo of nums whose sum is 0
    vector<vector<int>> threeSum(vector<int> nums)
    {
        vector<vector<int>> res;
        const int len = nums.size();

        sort(nums.begin(), nums.end());

        for (int i = 0; i < len - 2; ++i)
        {
            if (i > 0 && i < len && nums[i] == nums[i - 1])
                continue;
            int j = i + 1, k = len - 1;

            while (k > j)
            {
                const int key = nums[i] + nums[j] + nums[k];
                if (key == 0)
                {
                    res.push_back({nums[i], nums[j], nums[k]});
                    ++j, --k;
                    while (j < k && nums[j] == nums[j - 1])
                        ++j;
                    while (k > j && nums[k] == nums[k + 1])
                        --k;
                }
                else if (key > 0)
                    --k;
                else
                    ++j;
            }
        }

        return res;
    }
}

int main()
{
    Im::print<string>({"Hello,", "World!"});
}