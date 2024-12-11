#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    // Input reading
    int n, L1, L2;
    cin >> n >> L1 >> L2;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Dynamic programming array
    vector<long long> dp(n + 1, 0);
    deque<int> dq;

    long long max_gold = 0;

    for (int i = 1; i <= n; ++i) {
        // Remove elements from the deque that are out of the sliding window
        while (!dq.empty() && dq.front() < i - L2) {
            dq.pop_front();
        }

        // Update dp[i]
        if (!dq.empty() && dq.front() >= i - L1) {
            dp[i] = dp[dq.front()] + a[i];
        } else {
            dp[i] = a[i];
        }

        // Maintain deque to store potential indices for dp
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        // Update max_gold
        max_gold = max(max_gold, dp[i]);
    }

    cout << max_gold << endl;
    return 0;
}
