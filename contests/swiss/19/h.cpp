#include <bits/stdc++.h>
using namespace std;
const int SZ = 155333;
#define sz(x) (int)(x).size()
typedef vector<int> vi;

int32_t main(){
	int n ;
	cin >> n;
	map<string, string> opt;
	for(int i = 0 ; i < n; i ++){
		string s;
		cin >> s;	
		string w = s;
		sort((w).begin(), (w).end());
		if(!opt.count(w)) opt[w] = s;
		else{
			if(sz(opt[w]) > sz(s)) opt[w] = s;
			else if(sz(opt[w]) == sz(s)) opt[w] = min(opt[w] , s);
		}	
	}
	int q;
	cin >> q;
	while(q--){
		string p="";
		bool jb = false;
		string s;
		cin >> s;
		sort(s.begin() , s.end()); 
		for(int i = 0 ; i < (1<<sz(s)) ; i ++){
			string l;
			for(int j = 0 ; j < sz(s) ; j ++){
				if((1<<j) & i) l.push_back(s[j]);
			}
			if(opt.count(l)){
				if(!jb){
					jb = true;
					p = opt[l];
				}
				else{
					if(sz(opt[l]) > sz(p)) p = opt[l];
					else if(sz(opt[l]) == sz(p)) p = min(opt[l] , p);
				}
			}
		}
		if(!jb) cout <<"IMPOSSIBLE"<<endl;
		else cout << p << endl;
	}
}