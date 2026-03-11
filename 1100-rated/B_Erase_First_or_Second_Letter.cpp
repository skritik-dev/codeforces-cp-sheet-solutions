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
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        int res = 0;
        unordered_set<char> seen;

        for(int i = 0; i < n; i++) {
            seen.insert(s[i]);
            res += seen.size();
        }

        cout << res << nl;
    }
    return 0;
}

// Main Observation
// For a string s = "abcba"
// string of len = 5: a(bcba)
// string of len = 4: a(cba), b(cba)
// string of len = 3: a(ba), b(ba), c(ba)
// string of len = 2: a(a), b(b), c(b)
// string of len = 1: a, b, c

// You see, for any string of size n,
// The number of string of length k after performing the operations is the # of distinct character in the first (n - k + 1) characters
// And the last (k - 1) character remains the same in the length k string