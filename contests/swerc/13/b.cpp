#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) (x).begin, (x).end
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, int rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				trav(e, adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};


const int N = 110;
int a[N],b[N],s[N];
int clean[N][N];

int in1[N],in2[N],out1[N],out2[N];

const int inf = 1e9;
int cela(int x,int k){
	return (x+k-1)/k;
}

int32_t main(){
	int t;
	int z=0;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int id=0;
		for(int i=0;i<n;i++){
			cin >> a[i] >> b[i] >> s[i];
			in1[i] = id++;
			in2[i] = id++;
			out1[i] = id++;
			out2[i] = id++;
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin >> clean[i][j];
			}
		}

		int source = id++,sink = id++;
		Dinic D(id + 5);
		int tot=0;
	//	cout << source<<" "<<sink<<" ";
		for(int i=0;i<n;i++){
			D.addEdge(source,in1[i],inf);
			for(int j=0;j<n;j++){
				if(b[i] + clean[i][j] < a[j]){
					D.addEdge(out1[i],in2[j],inf);
				}
			}
			tot+=cela(s[i],m);

			D.addEdge(in1[i],out1[i],cela(s[i],m));
			D.addEdge(in2[i],out2[i],cela(s[i],m));
			D.addEdge(out2[i],sink,inf);
		}
		//cout << tot << endl;
		cout<<"Case "<<++z<<": ";
		cout << tot - D.calc(source,sink) << endl;
	}
}