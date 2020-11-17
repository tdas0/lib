#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

#define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll mod = (1000000007LL);
inline ll Mod(ll a, ll b){return (a%b);}
inline ll poww(ll a, ll b){ll res = 1;while (b > 0){if(b & 1) res = (res * a)%mod;a = (a * a)%mod;b >>= 1;}return res;}
ll gcd (ll a, ll b) { while (b) { a %= b,swap(a, b);}return a;}
void read(vector<int> &w, int n){w.resize(n);for(int i = 0; i < n; i++) cin>>w[i];}
void print(vector<int> &w){for(int i =0; i < sz(w); i++){if(i == sz(w) - 1) cout<<w[i]<<"\n";else cout<<w[i]<<" ";}}
int prodmod(vector<int> w);
int summod(vector<int> w);
///CUIDADO COM MAXN
#define N 300050

int n, m, q, k, v[N], ans;
// vector<int> grafo[N];
// pii w[N];
// string s;

int x[N], y[N];
map<int, vector<int> > mapa;

struct node {
	node *l = NULL;
	node *r = NULL;
	vector<pii> caras;
};

#define mid ((a+b)/2)
void upd(node *root, int a, int b, int i, pii valor){
	if(a == b) root->caras.pb(valor);
	else{
		if(i <= mid){
			if(!root->l) root->l=new node();
			upd(root->l, a,mid, i,valor);
		}
		else{
			if(!root->r)root->r=new node();
			upd(root->r, mid + 1, b, i,valor);
		}
	}
}
void fix(node *root){
	if(!root) return;
	fix(root->l);
	fix(root->r);
	if(root->l)for(auto w: root->l->caras) root->caras.pb(w);
	if(root->r)for(auto w: root->r->caras) root->caras.pb(w);
	sort(all(root->caras));
	// cout<<"carasss "<<sz(root->caras)<<"\n";
}

vector<pii> curr;

//percorre todas as posicoes >= X e pega os caras <= Y
void query(node *root, int a, int b, int i, int j, int Y){
	if(!root or root->caras.empty() or root->caras[0].f > Y or b < i or a > j) return;
	if(i <= a and j >= b){
		for(auto w: root->caras){
			if(w.f > Y) break;
			curr.pb(w);
		}
		return;
	}
	query(root->l, a, mid, i,j,Y);
	query(root->r, mid+1, b, i,j,Y);
}

int32_t main(){
	node *root = new node();
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>q;
	const int LIM = (int)(1e15), C = (int)3e9;
	for(int i = 1; i <= n; i++){
		int xi,yi;
		cin>>xi>>yi;
		x[i] = 2*yi - xi + C;
		y[i] = 2*yi + xi + C;
		swap(x[i], y[i]);
		upd(root, 0, LIM, x[i], {y[i], i});
	}

	fix(root);

	ll base = 5782344, ant=0;
	while(q--){
		int xi, yi, a, b;
		cin>>a>>b;
		xi = -1 - (ant + a)%mod;
		yi = (ant + b)%mod;
		int xm = 2*yi - xi + C;
		int ym = 2*yi + xi + C;
		swap(xm, ym);
		
		//quais caras tem yi <= ym e xi >= xm 
		curr.clear();
		query(root, 0, LIM, xm, LIM, ym);
		vector<ll> pos;
		for(auto x: curr) pos.pb(x.s);
		sort(all(pos));

		ll ans = 0, c=1LL;
		for(int i = 0; i <sz(pos); i++){
			ans += (pos[i]*c)%mod;
			c *= base;
			c%=mod;
			ans %=mod;
		}
		ant=ans;
		cout<<ans<<"\n";
		
	}
}
/*
    CUIDADO COM MAXN, MOD, OVERFLOW 
    >Colocar (>DEFINE INT LONG LONG<) no inicio do template
    >mod = (1e9 + 7), por padrao (NAO ESQUECER DE ALTERAR)
    >NAO ESQUECER DEFINE INT LONG LONG
    > N = 1 ? 
*/
int summod(vector<int> w){int curr=0;for(int i=0;i<sz(w); i++){curr = (curr+w[i])%mod;if(curr<0)curr+=mod;}return curr;}
int prodmod(vector<int> w){int curr = 1;
for(int i = 0; i < sz(w); i++){if(w[i] >= mod) w[i] %= mod;curr = (curr * w[i]) % mod;if(curr < 0) curr += mod;}return curr;}
