#include <bits/stdc++.h>
using namespace std;


struct event{
	int t;
	string s;
	string e;
	string c;
	int d;
	int S;
};


int32_t main(){
	int t;
	cin >> t;
	while(t--){
		int n , m ;
		cin >> n >> m;
		map<string, int>  C , P , K ;
		for(int i = 0 ; i < n; i ++){
			string s;
			cin >> s;
			int cat , pick , costp;
			cin>> cat >> pick >> costp;
			C[s] = cat , P[s] = pick , K[s] = costp;
		}
		vector<event> v;
		for(int i = 0 ; i < m ; i ++){
			event u;
			cin >> u.t >> u.s >> u.e;
			if(u.e == "p") cin >> u.c;
			if(u.e == "r") cin >> u.d;
			if(u.e == "a") cin >> u.S;
			v.push_back(u);
		}
		sort(v.begin() , v.end() , [&](event a , event b){
			if(a.t == b.t){
				int u = 0 , v = 0;
				if(a.e == "r") u = 2;
				if(b.e == "r") v = 2;
				if(a.e == "a") u = 1;
				if(b.e == "a") v = 1;
				return u < v;
			}
			return a.t < b.t;
		});
		for(int i = 0 ; i < m ; i ++){
			event u = v[i];
		}
		set<string> ok;
		map<string, string> incar;
		map<string, int> ans;
		for(int i = 0 ; i < m ; i ++){
			event u = v[i];
			if(u.e == "p"){
				if(incar.count(u.s)){
					ok.insert(u.s);
				}
				incar[u.s] = u.c;
				ans[u.s] += P[u.c];
			}
			if(u.e == "r"){
				if(!incar.count(u.s)){
					ok.insert(u.s);
				}
				else{
					ans[u.s] += K[incar[u.s]] * u.d;
					incar.erase(u.s);
				}
			}
			if(u.e == "a"){
				if(!incar.count(u.s)){
					ok.insert(u.s);
				}
				else{
					int r = C[incar[u.s]] * u.S;
					int z = r / 100 + (r%100 ? 1 : 0);
					ans[u.s] += z;
				}
			}
		}
		for(auto w : incar){
			ok.insert(w.first);
		}
		for(auto w : ok){
			ans[w] = 0;
		}
		for(auto w : ans){
			cout << w.first <<" " ;
			if(ok.count(w.first)){
				cout << "INCONSISTENT" << endl;
			}
			else cout << w.second << endl;
		}
	}
}