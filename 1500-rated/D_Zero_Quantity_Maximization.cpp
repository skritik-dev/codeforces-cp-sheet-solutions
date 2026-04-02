#include <bits/stdc++.h>
using namespace std;

// Macros
#define nl endl
#define pb push_back
#define ll long long int
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define vi vector<int>
#define vll vector<ll>
#define vs vector<string>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define vpll vector<pll>
#define ff first
#define ss second
#define asc(v) sort(v.begin(), v.end())
#define dsc(v) sort(v.begin(), v.end(), greater<int>())
#define secp(v) sort(v.begin(), v.end(), sortbysec)
#define mod 1000000007
#define rota(v, rotL) rotate(v.begin(), v.begin() + rotL, v.end())

// Sort by second
bool sortbysec(const pii &a, const pii &b) { return a.second < b.second; }

// Modular arithmetic
ll mod_add(ll a, ll b, ll m) { return ((a % m + b % m) % m + m) % m; }
ll mod_sub(ll a, ll b, ll m) { return ((a % m - b % m) % m + m) % m; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m * b % m) % m + m) % m; }
ll mod_pow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
ll mod_fact(ll n, ll p) {
    if (n >= p) return 0;
    ll res = 1;
    for (ll i = 1; i <= n; i++) res = mod_mul(res, i, p);
    return res;
}
ll large_mod(string num, ll a) {
    ll res = 0;
    for (char c : num) res = (res * 10 + (c - '0')) % a;
    return res;
}

// Math utilities
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll factorial(ll n) { ll f = 1; for (ll i = 2; i <= n; i++) f *= i; return f; }
ll nCr(ll n, ll r) { return factorial(n) / (factorial(r) * factorial(n - r)); }
ll countDigit(ll n) { ll cnt = 0; while (n) { n /= 10; cnt++; } return cnt; }
ll reverse(ll n) { ll res = 0; while (n) { res = res * 10 + n % 10; n /= 10; } return res; }
ll removeZero(ll n) {
    ll res = 0;
    while (n) { int d = n % 10; if (d) res = res * 10 + d; n /= 10; }
    ll rev = 0;
    while (res) { rev = rev * 10 + res % 10; res /= 10; }
    return rev;
}

// Bitwise utilities
string decToBin(ll n) {
    if (n == 0) return "0";
    string s = "";
    while (n) { s = char((n % 2) + '0') + s; n /= 2; }
    return s;
}
ll binToDec(string bin) {
    ll val = 0, base = 1;
    for (int i = bin.size() - 1; i >= 0; --i) {
        if (bin[i] == '1') val += base;
        base *= 2;
    }
    return val;
}

// Prime & Power checks
bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
bool isPowerOfTwo(ll n) { return n && !(n & (n - 1)); }
bool isPerfectSquare(ll n) {
    ll l = 1, r = n;
    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (m * m == n) return true;
        if (m * m < n) l = m + 1;
        else r = m - 1;
    }
    return false;
}

// Operations
vi removeDuplicatesVec(vi v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}
void swap(ll &a, ll &b) { ll t = a; a = b; b = t; }
vi factors(ll n) {
    vi f;
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) { f.pb(i); if (n / i != i) f.pb(n / i); }
    }
    asc(f);
    return f;
}
vector<int> sieve(int n) {
    vector<int> is_prime(n + 1, 1), primes;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.pb(i);
            for (int j = 2 * i; j <= n; j += i) is_prime[j] = 0;
        }
    }
    return primes;
}

// Custom hash for unordered_map
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename K, typename V>
using safe_umap = unordered_map<K, V, custom_hash>;

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    unordered_map<string, int> cnt;

    int extra = 0;
    for(int i = 0; i < n; i++) {
        int gcd_ = gcd(abs(a[i]), abs(b[i]));
        if(gcd_ > 0) { // Avoid division by zero
            a[i] /= gcd_;
            b[i] /= gcd_;
        }
        
        string key;
        if(a[i] == 0) {
            if(b[i] == 0) extra++;
            continue;
        } else if(b[i] == 0) {
            key = "1,0";
        } else if(a[i] < 0 && b[i] < 0) {
            key = to_string(-a[i]) + "," + to_string(-b[i]);
        } else if(a[i] > 0 && b[i] > 0) {
            key = to_string(a[i]) + "," + to_string(b[i]);
        } else if(a[i] < 0) { 
            key = to_string(a[i]) + "," + to_string(b[i]);
        } else {
            key = to_string(-a[i]) + "," + to_string(-b[i]);
        }
        cnt[key]++;
    }    

    int res = 0;
    for(const auto& it : cnt) {
        res = max(res, it.second);
    }

    cout << res + extra << nl;
}

// Main
int main() {
    fastio
    solve();
    return 0;
}