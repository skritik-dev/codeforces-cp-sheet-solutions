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

bool balanced(string s) {
    int balance = 0;
    for (char c : s) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int bal[n] {0};
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            bal[i] = (i == 0 ? 1 : bal[i - 1] + 1);
        } else {
            bal[i] = (i == 0 ? -1 : bal[i - 1] - 1);
        }
    }

    // Based on the graphical observation, if the bal[n - 1] is anywhere not zero, then we can't have balanced or reversed balanced strings
    if(bal[n - 1] != 0) {
        cout << "-1" << nl;
        return;
    }
    
    // We'll color 1 on the bracket above x-axis and 2 on the brackets below x-axis

    // If graph never goes below x-axis, then we can color everything with 1
    if(*min_element(bal, bal + n) == 0) {
        cout << "1" << nl;
        for(int i = 0; i < n; i++) {
            cout << "1 ";
        }
        cout << nl;
        return; 
    } else if(*max_element(bal, bal + n) == 0) { // If the graph never goes above x-axis, then we can color everything with 2
        cout << "1" << nl;
        for(int i = 0; i < n; i++) {
            cout << "1 ";
        }
        cout << nl;
        return;
    } else {
        cout << "2" << nl;
        for(int i = 0; i < n; i++) {
            if(bal[i] > 0) {
                cout << "1 ";
            } else if(bal[i] < 0) {
                cout << "2 ";
            } else {
                if(bal[i - 1] > 0)  {
                    cout << "1 ";
                } else {
                    cout << "2 ";
                }
            }
        }
        cout << nl;
        return;
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

