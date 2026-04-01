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
    v<int> nums(n);
    for(int i = 0; i < n; i++) cin >> nums[i];

    ll sum = 0, curr = 0;
    
    for(int i = 0; i <= n; i++) {
        if(i >= k) {
            sum += curr;
            curr -= nums[i - k];
        }

        if(i < n) curr += nums[i];
    }
    
    // Simple sliding window problem, but here new things are fixed FP notation and setprecision() function usage
    cout << fixed << setprecision(6) << (1.0 * sum) / (n - k + 1) << nl;
}

int main(void) {
    fastio;
    solve();
    return 0;
}