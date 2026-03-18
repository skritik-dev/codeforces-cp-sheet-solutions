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

    ll num;
    v<pair<ll, ll>> b;
    for(int i = 0; i < n; i++) { // Maintain the position information
        cin >> num;
        b.push_back({num, i});
    }
    sort(b.begin(), b.end()); // O(nlogn)

    // Maintaining a prefix sum array
    v<ll> prefix(n);
    prefix[0] = b[0].first;
    for(int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + b[i].first;

    v<int> res(n);

    for(int i = 0; i < n; i++) { // O(n)
        // Logic here
        int cnt = i, j = i;
        while(j < n) { // O(logn)
            pair<ll, ll> cmp = {prefix[j], INT_MAX};
            int k = upper_bound(b.begin(), b.end(), cmp) - b.begin();
            k--;
            if(j == k) break;
            cnt += (k - j);
            j = k;
        }

        res[b[i].second] = cnt;
    }

    for(int i = 0; i < n; i++) cout << res[i] << " ";
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