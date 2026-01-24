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

int main(void) {
    fastio;
    int t;
    cin >> t;
    while(t--) {
        int n, k, z;
        cin >> n >> k >> z;

        v<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        
        ll res = 0;

        // Finding the best left pair, we can use

        // After each left move we can go only in right direction

        // Approach is, going right. Then selecting the best pair in the path on which we can go left and then right
        for(int left = 0; left <= z && 2 * left <= k; left++) {
            int right = k - (2 * left);
            ll sum = accumulate(a.begin(), a.begin() + right + 1, 0LL);

            ll best_max_pair = INT_MIN;
            for(int i = 1; i <= right + 1; i++) {
                best_max_pair = max(best_max_pair, 0LL + a[i] + a[i - 1]);
            }

            ll total = sum + left * best_max_pair;
            res = max(res, total);
        }

        cout << res << nl;
    }
    return 0;
}