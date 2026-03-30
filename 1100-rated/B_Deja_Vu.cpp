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
    int n, q;
    cin >> n >> q;
    v<ll> a(n);
    v<int> x(q);

    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < q; i++) cin >> x[i];
    
    int last = 31;

    // This part is deceiving, as this loop runs atmost 30 times, O(30 * n)
    for(int i = 0; i < q; i++) { 
        if(x[i] >= last) continue;
        int div = pow(2, x[i]), add = pow(2, x[i] - 1);
        for(int j = 0; j < n; j++) {
            if(a[j] % div == 0) {
                a[j] += add;
            }
        }
        last = x[i];
    }

    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << nl;
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

// TC = O(t * 30 * n) = O(t * n) since 30 is a constant
// SC = O(n) for storing the array a