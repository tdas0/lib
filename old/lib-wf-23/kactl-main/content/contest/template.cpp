#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
// g++ -g a.cpp --std=c++17 -Wall -Wextra -Wno-unused-result -Wconversion -Wfatal-errors -o a.out
// -fsanitize=undefined,address (dont abuse, slow compiling)
// ulimit -s unlimited (change stack size)

// debug:
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...) 42
#endif
// usage: dbg(x,y,z); works for any printable thing
// compile: g++ name.cpp -DLOCAL && ./a.out


int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}
