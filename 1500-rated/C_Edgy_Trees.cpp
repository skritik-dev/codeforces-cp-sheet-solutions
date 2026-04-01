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

int dfs(int i, v<bool>& vis, v<v<int>>& adj) {
    int cnt = 1;
    for(const auto& ngbr : adj[i]) {
        if(!vis[ngbr]) {
            vis[ngbr] = true;
            cnt += dfs(ngbr, vis, adj);
        }
    }
    return cnt;
}

void solve() {
    int n, k;
    cin >> n >> k;
    // Instead i'll find the bad sequences and deleted them from the total to get all the good sequences
    v<v<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        // 0: Red and 1: Black
        if(c == 1) continue;
        
        // I'll keep the graph of with the red edges only, because that will contain the bad sequences

        // TIP: You can trip over the 1-based indexing, so make sure to convert it into 0-based indexing
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    // Now, need to find the connected components
    v<bool> vis(n, false);

    ll bad_sequences = 0;
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        vis[i] = true;
        int cnt = dfs(i, vis, adj); // Finding the size of connected components
        bad_sequences = (bad_sequences + bin_expo(cnt, k)) % MOD; // bad sequence will lie in the bad sequence only
    }

    ll good_sequences = (bin_expo(n, k) - bad_sequences + MOD) % MOD;
    cout << good_sequences << nl;
}

int main(void) {
    fastio;
    solve();
    return 0;
}