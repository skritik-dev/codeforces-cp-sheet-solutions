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
    v<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int curr_sum = 0, max_sum = INT_MIN;
    
    int i = 0;
    for(int j = 0; j < n; j++) {
        if(curr_sum < 0) { // Breakpoint (Start a new subarray, if subarray sum becomes negative)
            curr_sum = 0;
            i = j;
        }

        if(i < j) {
            if((arr[j] ^ arr[j - 1]) & 1) {
                curr_sum += arr[j];
            } else {
                curr_sum = arr[j]; // Breakpoint (Start a new subarray, if parity is adjacent parity is same)
                i = j;
            }
        } else {
            curr_sum = arr[j];
        }

        max_sum = max(max_sum, curr_sum);
    }

    cout << max_sum << nl;
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