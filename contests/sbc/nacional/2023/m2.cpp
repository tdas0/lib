#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
#define ff first
#define ss second
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<ll,ll> pll;



const ll inf = 1e18 + 10;
const int N = 1e6 + 10;
vector<pll> g[N];
int n,m;
vector<ll> DJ(int s,int exc){
    vector<ll> d(n+1,inf);
    priority_queue<pll,vector<pll>, greater<pll>> pq;
    d[s] = 0;
    pq.push({d[s] , s});
    while( !pq.empty()){
        auto [dd,v] = pq.top();
        pq.pop();
        if(dd != d[v])continue;
        for(auto [to,w] : g[v])if(to!= exc){
            if(d[to] > d[v] + w){
                pq.push(pll(d[to] = d[v] + w, to));
            }
        }
    }
    return d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    int P,G;
    cin >> P >> G;
    rep(i,0,m){
        int a,b,c;
        cin >> a >> b >> c;
        g[a].pb(pii(b,c));
        g[b].pb(pii(a,c));
    }
    vector<ll> d1 = DJ(P,-1),d2 = DJ(P,G);
    int ok=0;
    for(int i=1;i<=n;i++){
        if(i!=P && i!=G && d1[i] == 2ll * d1[G] && d2[i] > d1[i]){
            cout << i<<" ";
            ok = 1;
        }
    }
    if(!ok)cout <<"*";
    cout<<endl;
}
