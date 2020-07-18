#include <bits/stdc++.h>
#define N 100050
#define f first
#define s second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
int n;
int x[2][N], y[2][N], z[2][N];
vector<int> grafo[N];
struct dsu{
   int pai[N], peso[N];
    int Find(int x){
        if(x==pai[x]) return x;
        return pai[x] = Find(pai[x]);
    }
    int join(int a, int b){
        a = Find(a), b = Find(b);
        if(a== b) return 0;
        if(peso[a] > peso[b]) swap(a, b);
        pai[a]=b;
        if(peso[a]==peso[b])peso[b]++;
        return 1;
    }
    void init(){
        for(int i = 1; i < N; i++){
            pai[i]=i;
            peso[i]=0;
        }
    }
};
dsu d3, d2;
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	int cnt = 0,cnt2=0;
	d3.init();
	d2.init();
	map<pair<int, pii>, int> mapa;
	map<pii, int> mapa2;
	bool yes[2];
	yes[0]=yes[1]=0;
	set<pii> edges[2];
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 2; j++){
			cin>>x[j][i]>>y[j][i]>>z[j][i];
		}
		pair<int, pii> A = make_pair(x[0][i], pii(y[0][i], z[0][i]));
		pair<int, pii> B = make_pair(x[1][i], pii(y[1][i], z[1][i]));
		pii A2 = make_pair(x[0][i], y[0][i]);
		pii B2 = make_pair(x[1][i], y[1][i]);

		if(!mapa[A]) mapa[A] = ++cnt;
		if(!mapa[B]) mapa[B] = ++cnt;

		if(!mapa2[A2]) mapa2[A2] = ++cnt2;
		if(!mapa2[B2]) mapa2[B2] = ++cnt2;

		int p = mapa2[A2], q = mapa2[B2];
		int a = mapa[A], b = mapa[B];
		if(p != q and !edges[1].count({p, q})){
		// edges.insert({a, b});
			if(!d2.join(p, q)) yes[1] = 1;
			edges[1].insert({p, q});
			edges[1].insert({q, p});
		}
		if(a != b and !edges[0].count({a, b})){
			if(!d3.join(a, b)) yes[0] = 1;
			edges[0].insert({a, b});
			edges[0].insert({b, a});
		}
	}

	if(yes[0]) cout<<"True closed chains\n";
	else cout<<"No true closed chains\n";

	if(yes[1]) cout<<"Floor closed chains\n";
	else cout<<"No floor closed chains\n";
}