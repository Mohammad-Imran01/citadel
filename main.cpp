#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
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

        void insert(int key, int val)
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

    vector<vector<int>> fourSum(vector<int> nums, int target)
    {
        vector<vector<int>> res;
        const int len = nums.size();
        for (int i = 0; i < len - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1; j < len - 2; ++j)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                int k = j + 1, l = len - 1;
                while (k < l)
                {
                    int key = nums[i] + nums[j] + nums[k] + nums[l];
                    if (key == target)
                    {
                        res.push_back({nums[i], nums[j], nums[k], nums[l]});
                        ++k, --l;
                        while (k < l && nums[k] == nums[k - 1])
                            ++k;
                        while (l > k && nums[l] == nums[l - 1])
                            ++l;
                    }
                    else if (key < target)
                        ++k;
                    else
                        --l;
                }
            }
        }
        return res;
    }

    // max area to store water | trapping rainwater
    int maxArea(vector<int> heights)
    {
        int maxSize = 0;
        for (int i = 0, j = heights.size() - 1; i <= j;)
        {
            int ht = min(heights[i], heights[j]);
            int wd = j - i;
            maxSize = max(maxSize, wd * ht);
            if (heights[i] < heights[j])
                ++i;
            else
                --j;
        }

        return maxSize;
    }

    int minInRotatedSortedArray(vector<int> nums)
    {
        if (nums.empty())
            return -1;
        int mini = 1e9;

        for (int left = 0, right = nums.size() - 1; left <= right;)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return -1;
    }

    string longestPalindrom(string word)
    {
        int beg{}, count{1};

        auto solve = [&](int left, int right)
        {
            while (left >= 0 && right < word.size() && word[left] == word[right])
            {
                if (right - left + 1 > count)
                {
                    count = right - left + 1;
                    beg = left;
                }
                --left, ++right;
            }
        };

        for (int i = 0; i < word.size(); ++i)
        {
            solve(i, i);
            solve(i, i + 1);
        }

        return word.substr(beg, count);
    }

    vector<vector<int>> mergeIntervals(vector<vector<int>> &vals)
    {
        if (vals.size() < 2)
            return vals;

        sort(vals.begin(), vals.end());

        vector<vector<int>> res{vals[0]};

        int i = 1;

        while (i < vals.size())
        {
            if (res.size() && res.back()[1] >= vals[i][0])
            {
                res.back()[1] = max(vals[i][1], res.back()[1]);
                res.back()[0] = min(res.back()[0], vals[i][0]);
            }
            else
            {
                res.push_back(vals[i]);
            }
            ++i;
        }

        return res;
    }

    int maxSubarray(vector<int> nums)
    {
        int maxi = -1e8;

        int curr = -1e8;
        for (int i = 0; i < nums.size(); ++i)
        {
            curr = max(nums[i], curr + nums[i]);
            maxi = max(maxi, curr);
        }
        return maxi;
    }
    vector<vector<string>> groupAnagram(vector<string> words)
    {
        if (words.empty())
            return {};
        unordered_map<string, vector<string>> mp;
        vector<vector<string>> res;

        for (const auto &word : words)
        {
            string s = word;
            sort(s.begin(), s.end());
            mp[s].push_back(word);
        }

        for (auto &[_, group] : mp)
            res.push_back(group);

        return res;
    }
} // array / strings
namespace Im
{
    struct Node
    {
        int val;
        Node *next = nullptr;

        Node(int val_ = 0, Node *next_ = nullptr)
            : val(val_), next(next_) {}
    };
    bool findCycle(Node *root)
    {
        Node *temp = new Node(0, root);
        Node *fast = temp, *slow = temp;

        while (true)
        {
            slow = slow->next;
            if (!fast->next || !fast->next->next)
                return false;
            fast = fast->next->next;

            if (fast == slow)
                return true;
        }
        return false; // will never reach
    }
    Node *mergeTwoLists(Node *list1, Node *list2)
    {
        Node *temp = new Node;
        Node *curr = temp;
        while (list1 || list2)
        {
            if (!list1)
            {
                curr->next = list2;
                list2 = list2->next;
            }
            else if (!list2)
            {
                curr->next = list1;
                list1 = list1->next;
            }
            else
            {
                if (list1->val < list2->val)
                {
                    curr->next = list1;
                    list1 = list1->next;
                }
                else
                {
                    curr->next = list2;
                    list2 = list2->next;
                }
            }
            curr = curr->next;
        }
        return temp->next;
    }
    Node *addTwoNumbers(Node *l1, Node *l2)
    {
        Node *temp = new Node;
        Node *curr = temp;

        int carry = 0;
        while (l1 || l2 || carry)
        {
            if (l1)
            {
                carry += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                carry += l2->val;
                l2 = l2->next;
            }
            Node *t = new Node(carry % 10);
            carry /= 10;
            curr->next = t;
            t = nullptr;
            curr = curr->next;
        }
        return temp->next;
    }
    Node *reverseList(Node *root, Node *end = nullptr)
    {
        Node *prev = nullptr;
        while (root != end)
        {
            Node *t = root->next;
            root->next = prev;
            prev = root;
            root = t;
        }
        return prev;
    }
    Node *revKSize(Node *root, int k)
    {
        if (!root || !root->next || k <= 1)
            return root;
        vector<Node *> temp;
        while (root)
        {
            temp.push_back(root);
            root = root->next;
        }
        for (int i = 0; i + k <= temp.size(); i += k)
            reverse(temp.begin() + i, temp.begin() + i + k);

        for (int i = 1; i < temp.size(); ++i)
            temp[i - 1]->next = temp[i];
        temp.back()->next = nullptr;
        return temp.front();
        // Node dummy(0, root);
        // Node *temp = &dummy;

        // while (true)
        // {
        //     Node *p = &dummy, *packEnd = &dummy;

        //      for (int i = 0; i < k; ++i)
        //     packEnd = packEnd->next;
        //     Node* newGroupEnd = packEnd;

        //     Node* newGroup

        // }
    }
} // linked list
int main()
{
    Im::print<string>({"Hello,", "World!"});
    cout << "substr withotrep char: " << Im::longestSubstringWithoutRepChar("Hello");
}