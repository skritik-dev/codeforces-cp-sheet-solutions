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

bool check(int mid, vector<int> a, vector<int> b) {
    for(int i = 0; i < mid; i++) { // Performing remove operation on largest a and smallest b to preserve the ai < bi
        a.pop_back();
        b.pop_back();
    }

    sort(b.begin(), b.end()); // Sorting b in ascending order again after removing smallest elements
    for(int i = 0; i < (int) a.size(); i++) {
        if(a[i] >= b[i]) return false;
    }
    return true;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(n);

    // Acc. to the problem statement, a[0] is always 1
    a[0] = 1;
    for(int i = 1; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    // Starting the matching process ai < bi, increases the chance of successful matches
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    int l = 0, r = n;
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(check(mid, a, b)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << nl;
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

// TC = O(nlogn)
// SC = O(n)

// Can't use multiset's upper_bound, because:
// multiset iterators are bidirectional
// upper_bound bidirectional iterators is linear
// so we get O(n), not O(log n)
// hence, the tc is O(n^2) instead of O(nlogn)
// Instead, i can see that answer is monotonic in nature
// If k = 5 if first valid answer, then k > 5 will also be valid
// This indicates me to use "binary search on the answer"