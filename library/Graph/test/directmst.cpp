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

// begin of dsu

struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		rep(i,0,n+1) p[i] = i;
	}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};	
// end

// begin of dmst


struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

ll dmst(int n, int r, vector<Edge>& g) {
	dsu uf(n);
	vector<Node*> heap(n);
	trav(e, g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n);
	seen[r] = r;
	rep(s,0,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			path[qi++] = u, seen[u] = s;
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u);
				heap[u] = cyc, seen[u] = -1;
			}
		}
	}
	return res;
}

// end

int n;

int32_t main(){
	cin >> n;
	vector<Edge> v;
	rep(i,1,n+1){
		int xi ,si;
		cin >> xi >> si;
		v.push_back({xi,i,si});
		rep(j,0,n+1){
			int cost;
			cin >> cost;
			v.push_back({j,i,cost});
		}
	}
	cout << dmst(n+1,0,v) << endl;
}