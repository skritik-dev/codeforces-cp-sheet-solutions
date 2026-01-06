#include <bits/stdc++.h>
using namespace std;

template <typename T> using pq = priority_queue<T>;
template <typename T> using v = vector<T>;
template <typename T> using vv = vector<vector<T>>;
template <typename T> using stk = stack<T>;
template <typename T> using q = queue<T>;
#define ll long long
#define pii pair<int, int>
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define nl "\n"
#define MOD 1000000007
#define ff first
#define ss second

ll modInverse(ll a, ll mod) {
    ll res = 1;
    ll power = mod - 2;
    while (power) {
        if (power & 1)
            res = res * a % mod;
        a = a * a % mod;
        power >>= 1;
    }
    return res;
}

int nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    ll res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - r + i) % MOD;
        res = res * modInverse(i, MOD) % MOD;
    }
    return (int)res;
}

ll bin_expo(ll a, ll b) {
    ll result = 1;
    while (b) {
        if (b & 1)
            result = (result * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return result;
}

void solve() {
    int n, k;
    cin >> n >> k;

    
    v<ll> nums(n);
    ll mn = LLONG_MAX;
    
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        mn = min(mn, nums[i]);
    }
    
    if(k >= 3) {
        cout << 0 << nl;
        return;
    }
    
    v<ll> diff;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            diff.push_back(abs(nums[j] - nums[i]));
        }
    }

    sort(diff.begin(), diff.end());

    ll ans = min(mn, diff[0]);

    if(k == 2) {
        for(int i = 0; i < n; i++) {
            auto it = lower_bound(diff.begin(), diff.end(), nums[i]); // find smallest x >= nums[i]
            if(it != diff.end()) {
                ans = min(ans, abs(nums[i] - *it));
            } if(it != diff.begin()) { // x may lie smaller than nums[i], we'll just move immediate left
                it--;
                ans = min(ans, abs(nums[i] - *it));
            }
        }
    }  

    cout << ans << nl;
}

int main(void) {
    fastio;
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

// Observation: If we have atleast k = 3, then we can always have minimum element as 0.

// TC = O(n^2 log(n^2)) = O(n^2 log n) due to sorting of differences array
// SC = O(n^2) for storing differences array