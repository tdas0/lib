#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
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

ll modpow(ll b, ll e ,ll mod){
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
int id_p = 0 ;
const int N = 300005;
map<pii , int> id_bag;
int get_id(pii x){
	if(id_bag.count(x)) return id_bag[x];
	return id_bag[x] = ++ id_p;
}
struct SCC{
	vector< vi> g , comps;
	vi val, z, cont, cp;
	int Time =0, ncomps= 0 , n; 
	SCC(vector<vi> g, int n ):n(n) , g(g) , val(n+1,0), cp(n+1, -1) {}
	int dfs(int j){
		int low = val[j] = ++Time , x ; z.push_back(j);
		for(int pp = 0 ; pp < g[j].size() ; pp++){
		int e = g[j][pp];
		if(cp[e] < 0)
			low = min(low , val[e] ?: dfs(e));
		}
		if(low == val[j]){
			do{
				x = z.back() ; z.pop_back();
				cp[x] = ncomps;
				cont.push_back(x);
			} while(x != j);
			comps.push_back(cont) , cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	void scc(){
		val.assign(300000,0); cp.assign(300000,-1);
		Time = 0;
		ncomps = 1;
		rep(i,1,n+1) if(cp[i] < 0 ) dfs(i);
	}
};
int op[N] , lt[N] , lv[N] , rt[N] , rv[N], dp[N] , dg[N];
vpi g[N];
bool has[N];
int32_t main(){
	int n ,k ;
	cin >> n >> k;
	for(int i = 1 ;i <= n; i ++){
		cin >> op[i] >> lt[i] >> lv[i] >> rt[i] >> rv[i];
		get_id(pii(lt[i], lv[i])) , get_id(pii(rt[i] , rv[i]));
	}
	vector<vi> Gsc(id_p+1);
	for(int i = 1; i <= n; i ++) if(!op[i]){
		Gsc[get_id(pii(lt[i], lv[i]))].push_back(get_id(pii(rt[i] , rv[i])));
	}
	SCC scc(Gsc, id_p);
	scc.scc();
	for(map<pii, int>::iterator it = id_bag.begin() ; it != id_bag.end() ;  it++){
		pair<pii , int > w = *it;
		if(w.first.first){
			if(!has[scc.cp[w.second]]){
				has[scc.cp[w.second]] = 1;
				dp[scc.cp[w.second]] = w.first.second;
			}
			if(dp[scc.cp[w.second]] != w.first.second){
				cout << "NO\n";
				return 0;
			}
		}
	}
	for(int i = 1; i <= id_p ; i ++) for(int j = 0 ; j < Gsc[i].size() ; j ++){
		int w = Gsc[i][j];
		if(scc.cp[i] != scc.cp[w]){
			g[scc.cp[i]].push_back(pii(scc.cp[w],0));
			dg[scc.cp[w]] ++ ;
		}
	}
	for(int i = 1; i <= n; i ++) if(op[i]){
		g[scc.cp[get_id(pii(lt[i] , lv[i]))]].push_back(pii(scc.cp[get_id(pii(rt[i] , rv[i]))],1));
		dg[scc.cp[get_id(pii(rt[i] , rv[i]))]]++;
	}
	queue<int> q;
	for(int i = 1 ; i <= id_p;  i++){
		if(!dg[i]) q.push(i);
	}
	for(int i = 1; i <= id_p; i ++){
		if(!has[i]) dp[i] = -2000000000;
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int j =0 ; j < g[u].size() ; j ++){
			pii w = g[u][j];
			dg[w.first] --;
			if(w.second){
				dp[w.first] = max(dp[w.first] , dp[u] + 1);
			}
			else{
				dp[w.first] = max(dp[w.first] , dp[u]);
			}
			if(dg[w.first] == 0) q.push(w.first);
		}
	}
	for(int i = 1; i <= n; i ++){
		int u = get_id(pii(lt[i] , lv[i])) , v = get_id(pii(rt[i] , rv[i]));
		if(op[i]){
			if(dp[scc.cp[u]] >= dp[scc.cp[v]]){
				cout <<"NO\n";
				return 0;
			}
		}
		else{
			if(dp[scc.cp[u]] > dp[scc.cp[v]]){
				cout <<"NO\n";
				return 0;
			}
		}
	}
	for(map<pii, int>::iterator it = id_bag.begin() ; it != id_bag.end() ;  it++){
		pair<pii , int > w = *it;
		if(w.first.first){
			if(!has[scc.cp[w.second]]){
				has[scc.cp[w.second]] = 1;
				dp[scc.cp[w.second]] = w.first.second;
			}
			if(dp[scc.cp[w.second]] != w.first.second){
				cout << "NO\n";
				return 0;
			}
		}
	}
	cout <<"YES\n";
	for(int i = 1; i  <= k ; i++){
		cout << dp[scc.cp[get_id(pii(0,i))]] << endl;
	}
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/