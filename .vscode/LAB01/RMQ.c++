#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(2 * n);
        // Build the tree
        for (int i = 0; i < n; ++i) {
            tree[n + i] = data[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // Function to return the minimum value in range [left, right]
    int range_min(int left, int right) {
        left += n;
        right += n + 1;
        int min_val = INT_MAX;
        while (left < right) {
            if (left % 2 == 1) {
                min_val = min(min_val, tree[left]);
                left++;
            }
            if (right % 2 == 1) {
                right--;
                min_val = min(min_val, tree[right]);
            }
            left /= 2;
            right /= 2;
        }
        return min_val;
    }

private:
    int n;
    vector<int> tree;
};

int main() {
    // Input number of elements in the array
    int n;
    cin >> n;
    vector<int> a(n);

    // Input the array elements
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Build the segment tree
    SegmentTree segmentTree(a);

    // Input number of queries
    int m;
    cin >> m;

    int total_sum = 0;

    // Process each query and compute the total sum of minimum values
    for (int i = 0; i < m; ++i) {
        int left, right;
        cin >> left >> right;
        total_sum += segmentTree.range_min(left, right);
    }

    // Output the result
    cout << total_sum << endl;

    return 0;
}
