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

vector<ll> fact;
void precompute(int n) {
    fact.assign(n + 1, 0);
    fact[0] = 1;   
    for(int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;  
    }
}

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

    int total_and;
    v<int> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        if(i == 0) total_and = nums[0];
        total_and &= nums[i];
    }

    // AND(1, 1)     = AND(2, n)
    // AND(1, i)     = AND(i + 1, n)
    // ...
    // AND(1, n - 1) = AND(n, n)
    // From the last condition AND(1, n) = AND(1, n - 1) & AND(n, n) = AND(1, n - 1) & a[n]
    // From the first condition AND(1, 1) = AND(2, n) = a[1] & AND(2, n)
    // See the prefix is decreasing and suffix is increasing
    // So, let's pref(i) = suff(i) and then pref(i + 1) = suff(i + 1)
    // pref(i) >= pref(i + 1) and suff(i) <= suff(i + 1)
    // pref(i) = x, pref(i + 1) = x - d
    // suff(i) = x, suff(i + 1) = x - d, suffix cannot decrease (CONTRADICTION)
    // So, all prefixes must be equal, and it's equal to TOTAL_AND of the array, as proved above
    // So, we need elements equal to TOTAL_AND at front and back of the array

    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += (nums[i] == total_and)? 1 : 0;
    }
    precompute(n);
    ll res = ((cnt * (cnt - 1)) % MOD * fact[n - 2]) % MOD;
    cout << res << nl;
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

