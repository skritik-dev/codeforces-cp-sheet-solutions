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
    string s;
    cin >> s;

    // The basic idea is: when I shift the k-window, the element at ith index is added and (i % k)th index is reomved
    // Suppose the current k-window is balanced, then upon shifting to next k-window, the element removed must be equal to the element added
    for(int i = k; i < n; i++) {
        if(s[i] == '0') {
            if(s[i % k] == '1') {
                cout << "NO" << nl;
                return;
            } else {
                s[i % k] = '0';
            }
        } else if(s[i] == '1') {
            if(s[i % k] == '0') {
                cout << "NO" << nl;
                return;
            } else {
                s[i % k] = '1';
            }
        }
    }

    // The remaining ? will adjust themselves according to the scenerio
    int z = 0, o = 0;
    for(int i = 0; i < k; i++) {
        z += (s[i] == '0')? 1 : 0;
        o += (s[i] == '1')? 1 : 0;
    }

    if(z > k / 2 || o > k / 2) {
        cout << "NO" << nl;
    } else {
        cout << "YES" << nl;
    }
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