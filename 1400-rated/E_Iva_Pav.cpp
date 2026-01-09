#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

int nums[200001];
int pref[31][200001]; 
// pref[bit][i] = number of ones in bit `bit` in nums[0..i-1]

int range_and(int l, int r) {
    int ans = 0;
    int len = r - l + 1;

    for (int bit = 0; bit < 31; bit++) {
        int ones = pref[bit][r + 1] - pref[bit][l];
        if (ones == len) {
            ans |= (1 << bit);
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // build prefix sums (1-based)
    for (int bit = 0; bit < 31; bit++) {
        pref[bit][0] = 0;
        for (int i = 0; i < n; i++) {
            pref[bit][i + 1] = pref[bit][i];
            if (nums[i] & (1 << bit)) {
                pref[bit][i + 1]++;
            }
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int l, k;
        cin >> l >> k;
        l--;

        if (nums[l] < k) {
            cout << -1 << ' ';
            continue;
        }

        // right-biased binary search
        int low = l, high = n - 1;
        while (low < high) {
            int mid = low + (high - low + 1) / 2; // Right biased because i'm looking for the maximum index
            if (range_and(l, mid) >= k) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        cout << low + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    fastio;

    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
}

// Time Complexity: O((n + q * logn) * 31) per test case
// Space Complexity: O(n * 31)

// Explanation:
// For each bit, i maintain a prefix sum array of number of set bits for each index.
// We have a property of AND, for a number a, a & b <= a
// So, we can see the monotonic nature of the AND operation here
// Due to monotonic nature, we can binary search for the maximum index
// We will binary search my way to the maximal index where AND from l to that index is >= k
// To get AND from l to r in O(1), we can use the prefix sums