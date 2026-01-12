#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define nl "\n"
#define MOD 1000000007

// hash for pair<int,int>
struct pair_hash {
    size_t operator()(const pii& p) const {
        return ((uint64_t)p.first << 32) ^ (uint32_t)p.second;
    }
};

unordered_map<pii, int, pair_hash> idx;
vector<vector<int>> adj;
vector<int> res;

void dfs(int chd, int par) {
    for (int ngbr : adj[chd]) {
        if (ngbr == par) continue;

        if (idx[{par, chd}] < idx[{chd, ngbr}]) {
            res[ngbr] = res[chd];
        } else {
            res[ngbr] = res[chd] + 1;
        }

        dfs(ngbr, chd);
    }
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, {});
    res.assign(n + 1, 0);
    idx.clear();

    int u, v;

    // fake parent edge for root
    idx[{1, -1}] = -1;
    idx[{-1, 1}] = -1;

    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        idx[{u, v}] = i;
        idx[{v, u}] = i;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    res[1] = 1;
    dfs(1, -1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, res[i]);
    }

    cout << ans << nl;
}

int main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
