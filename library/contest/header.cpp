#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down


// Pretty good compilation command:
// g++ -g a.cpp --std=c++17 -Wall -Wextra -Wno-unused-result -Wconversion -Wfatal-errors -o a.out
// -fsanitize=undefined,address (dont abuse, slow compiling)
// ulimit -s unlimited (change stack size)


// naim:
// g++ -g b.cpp --std=c++17 -Wall -Wextra -Wno-unused-result -Wconversion -Wfatal-errors -fsanitize=undefined,address && ./a.out 
