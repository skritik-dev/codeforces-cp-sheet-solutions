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

bool solve(int k, vector<pii>& nums) {
    int curr_min_pos = 0, curr_max_pos = 0;

    for(int i = 0; i < nums.size(); i++) {
        curr_min_pos -= k;
        curr_max_pos += k;

        // Clamping wrt. current interval
        curr_min_pos = max(curr_min_pos, nums[i].first);
        curr_max_pos = min(curr_max_pos, nums[i].second);

        if(curr_min_pos > curr_max_pos) return false;
    }

    return true;
}

int main(void) {
    fastio;
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        
        vector<pii> segments(n);
        for(int i = 0; i < n; i++) {
            cin >> segments[i].first >> segments[i].second;
        }

        int l = 0, r = 1e9;
        while(l < r) {
            // Observation: We need to get the best possible minimum answer -> that's the intuition of binary search
            int mid = l + (r - l) / 2; // Value of k
            if(solve(mid, segments)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
    
        cout << l << nl;
    }
    return 0;
}

// TC = O(nlogm) where m = max coordinate value
// SC = O(n)