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
    // Given m, for any number to be greater than 10^m, it should have at least m + 1 digits
    // numDigits > m, then sasha wins
    // numDigits <= m, then anna wins

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> trailingZeros(n, 0);

    int numDigits = 0;
    for(int i = 0; i < n; i++) {
        // Count the trailing zeros
        while(a[i] % 10 == 0) {
            a[i] /= 10;
            numDigits++;
            trailingZeros[i]++;
        }

        // Remaining digits after removing trailing zeros
        while(a[i] > 0) {
            a[i] /= 10;
            numDigits++;
        }
    }

    sort(trailingZeros.rbegin(), trailingZeros.rend());

    // Optimal play for anna: Reduce the digits, by reversing the number with most amount of trailing zeros, i.e. 1000 -> 0001 ~ 1
    // Optimal play for sasha: Protect the digits, by protecting the number with most amount of trailing zeros from being reversed, i.e. choose 1000 and 1 -> 10001
    // But sasha can only protect one number with trailing zeros at a time, 1000 and 10 -> 100010

    // First anna reverses the maximum number of trailing zeros, then sasha protects the next maximum number of trailing zeros
    for(int i = 0; i < n; i += 2) {
        numDigits -= trailingZeros[i];
    }

    if(numDigits > m) {
        cout << "Sasha" << nl;
    } else {
        cout << "Anna" << nl;
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