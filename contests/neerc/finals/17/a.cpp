#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct query{
	ll t , x, y , id;
};

set<ll> bp[63];
map<ll, ll> id , vx;
int32_t main(){
	int n;
	cin >> n;
	vector<query> v(n);
	for(int i =0  ; i< n; i ++ ){
		cin >> v[i].t >> v[i].x >> v[i].y;
		v[i].id = i ;
	}
	for(int i = 0 ; i < n; i ++){
		if(v[i].t == 1){
			ll xz = v[i].y;
			ll cnt = 0;
			while(xz > 0ll){
				xz /=2ll;
				cnt ++ ;
			}
			bp[cnt].insert(v[i].x);
			vx[v[i].x] = v[i].y;
			id[v[i].x] = v[i].id;	
		}
		else{
			bool can = false;
			for(int j = 0 ; j < 63; j ++){
				set<ll>::iterator it = bp[j].lower_bound(v[i].x);
				if(it != bp[j].begin()){
					set<ll>::iterator zt = it;
					zt--;
					ll x = *zt;
					ll y = vx[x];
					if((x - v[i].x)*(x - v[i].x) + (y-v[i].y)*(y-v[i].y) < (y*y)){
						can = true;
						cout << id[x]+1 << endl;
						bp[j].erase(x);
						id.erase(x);
						vx.erase(x);
						break ; 
					} 
				}
				if(bp[j].lower_bound(v[i].x) != bp[j].end()){
					set<ll>::iterator zt = bp[j].lower_bound(v[i].x);
					ll x = *zt;
					ll y = vx[x];
					if((x - v[i].x)*(x - v[i].x) + (y-v[i].y)*(y-v[i].y) < (y*y)){
						can = true;
						cout << id[x] +1 << endl;						
						bp[j].erase(x);
						id.erase(x);
						vx.erase(x);
						break ; 
					}					
				}
			}
			if(!can) cout << -1 << endl;
		}
	}

}