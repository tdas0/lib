#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
 
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
ll mod = (1000000007LL);
 
inline ll poww(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if(b & 1) res = (res * a)%mod;
        a = (a * a)%mod;
        b >>= 1;
    }
    return res;
}
inline pii operator+(pii A, pii B){
    return pii(A.f + B.f, A.s + B.s);
}
inline pii operator-(pii A, pii B){
    return pii(A.f - B.f, A.s - B.s);
}
inline ll mult(ll a, ll b){
    return (a * b) % mod;
}
 
ll gcd (ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
 
/*
    >Colocar (>DEFINE INT LONG LONG<) no inicio do template
    >mod = (1e9 + 7), por padrao (NAO ESQUECER DE ALTERAR)
    >NAO ESQUECER DEFINE INT LONG LONG
    > N = 1 ? 
*/
 
///CUIDADO COM MAXN
#define N 2000050
 
int n, m, q, k, v[N], vis[N];
 
pii TT, w[N];
 
string s;
int g[N];
vector<pii> grafo[N];
vi tour;
int del[N];
inline void find(int u){
    vector<int>pilha;
    pilha.pb(u);
    while(!pilha.empty()){
        int x = pilha.back();
        while(!grafo[x].empty() and del[grafo[x].back().s]){
            g[x]--;
            grafo[x].pop_back();
        }
        if(!g[x]){
            tour.pb(x);
            pilha.pop_back();
            continue;
        }
        auto v = grafo[x].back();
        grafo[x].pop_back();
        g[x] --;
        del[v.s] = 1;
        pilha.pb(v.f);
    }
}
 
vector<pii> all;
int rem[N];
int32_t main()
{
    ios::sync_with_stdio(false); cin.tie(0);
 
    cin>>n>>m;
    for(int i = 1,a, b; i <= m; i++){
        cin>>a>>b;
        if(b<a)swap(a,b);
        all.pb({a, b});
        grafo[a].pb({b,i});
        grafo[b].pb({a,i});
        g[a]++;
        g[b]++;
    }
    for(int i = 1; i <= n; i++){
        if(g[i] % 2 == 0) continue;
        g[0] ++, g[i]++;
        grafo[0].pb({i, m+i});
        grafo[i].pb({0, m+i});
        // cout<<"alo 0 "<<i<<"\n";
    }
    vector<pii> r;
    for(int i = 0; i <= n; i++){
        if(vis[i]) continue;
        find(i);
        cout << tour.size() << endl;
        for(int i = 1; i < sz(tour)-1; i += 2){
            int x = tour[i], v = tour[i + 1];
            int u = (i >= 1? tour[i - 1]:-1), w = (i + 2 < sz(tour) ?tour[i + 2] :-1);
            cout << x <<" " << v << " " << u <<" " << w << " " << rem[i-1] <<" " << rem[i] <<" " << rem[i+1] << endl;
            if(!x or !v) rem[i]=1;
            else{
                if(!u and !rem[i-1]) rem[i-1]=1;
                else if(!w) rem[i+1]=1;
                else r.pb({min(x,v),max(x,v)}), rem[i]=1;
            }
        }
 
        tour.clear();
    }
    vector<pii>ans;
    sort(all(r));
    for(auto w: all)
        if(!binary_search(all(r), w))
            ans.pb(w);
    // for(auto w: tour)cout<<w<<"\n";
 
    // cout<<sz(ans)<<"\n";
    // for(auto w: ans) cout<<w.f<<" "<<w.s<<"\n";
}