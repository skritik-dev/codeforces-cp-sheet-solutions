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
    int n;
    cin >> n;
    v<ll> nums(n);
    unordered_map<ll, vector<int>> seen;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        // Storing two indices for same number
        seen[nums[i]].push_back(i);
    }

    unordered_set<int> res;
    ll T = accumulate(nums.begin(), nums.end(), 0LL);

    for(int i = 0; i < n; i++) {
        ll req = T - 2 * nums[i];
        if(!seen[req].empty()) {
            for(const auto& idx : seen[req]) {
                if(i != idx) res.insert(idx);
            }
        }
    }

    int m = res.size();
    cout << m << nl;
    for(const auto& idx : res) cout << idx + 1 << " ";
    cout << nl;
}

int main(void) {
    fastio;
    solve();
    return 0;
}