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
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

typedef vector<int> bignum;
const int base = 1000*1000*1000;

// aho

struct AhoCorasick {
	enum {alpha = 256, first = 0};
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vector<int> backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		trav(c, s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) {
		N.emplace_back(-1);
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		trav(c, word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i,0,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
// end
// begin of bigint
void print(bignum & a) {
	printf("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i) {
		printf("%09d", a[i]);
	}
}

void fix(bignum & a) {
	while (a.size() > 1u && a.back() == 0) {
		a.pop_back();
	}
}
void int2bignum(int n, bignum & a) {
	a.clear();
	if (n == 0) a.push_back(0);
	while(n > 0) {
		a.push_back(n%base);
		n /= base;
	}
}
void sum(bignum & a, bignum & b, bignum & c) {
	int carry = 0, n = max(a.size(), b.size());
	c.resize(n);
	for (int i=0, ai, bi; i<n; i++) {
		ai = i < (int)a.size() ? a[i] : 0;
		bi = i < (int)b.size() ? b[i] : 0;
		c[i] = carry + ai + bi;
		carry = c[i] / base;
		c[i] %= base;
	}
	if (carry > 0) c.push_back(carry);
	fix(c);
}

// end

bignum dp[101][1010];
int n , m , p;
vs v;
int32_t main(){
	cin >> n >> m >> p;
	v = vs(p);
	string alfa;
	cin >> alfa;
	vector<char> al;
	rep(i,0,sz(alfa)) al.push_back(alfa[i]);
	sort(all(al));
	map<char,int> ppos;
	int ct = 0;
	set<char> ff;
	allin(w,al) ff.insert(w);
	allin(w,ff) ppos[w] = ct++;
	rep(i,0,p) cin >> v[i];
	rep(i,0,p){
		rep(j,0,sz(v[i])) v[i][j] = ppos[v[i][j]];
	}
	AhoCorasick aho(v);
	int k = sz(aho.N);
	int2bignum(1, dp[0][0]);
	rep(i,0,m){
		rep(j,0,k){
			rep(f, 0, n){
				int x = aho.N[j].next[f];
				bignum carry = dp[i+1][x];
				if(!aho.N[x].nmatches)
					sum(dp[i+1][x] , dp[i][j] , carry);
				swap(dp[i+1][x] , carry);
			}
		}
	}
	bignum ans;
	ans.clear();
	rep(j,0,k){
		bignum pp;
		sum(ans , dp[m][j] , pp);
		swap(pp,ans);
	} 
	print(ans);
}