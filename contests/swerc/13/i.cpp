#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
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

queue<map<string, int> > q;
map<string,int> freq;
set<pair<int,string>> ss;
int32_t main(){
	string s;
	while(cin >> s){	
		map<string,int> curr;
		if(s == "<text>"){
			string p;
			while(cin >> p && p != "</text>"){
				if(sz(p) < 4) continue;
				ss.erase({-freq[p] , p});
				curr[p] ++ ;
				freq[p] ++;
				ss.insert({-freq[p] , p});
			}
			q.push(curr);
		}
		else{
			int x;
			cin >> x;
			string p;
			cin >> p;
			// imprime top x
			cout <<"<top "<<x<<">"<<endl;
			// imprime aqui
			int ct = 0 , fr = 0;
			for(auto ww : ss){
				pair<string,int> w = {ww.second , -ww.first};
				if(w.second == 0) break ;
				if(ct < x){
					ct ++ ;
					cout << w.first <<" " << w.second << endl;
					fr = w.second;
				}
				else{
					if(fr == w.second) cout << w.first <<" " << w.second << endl;
				}
			}
			cout << "</top>" << endl;
		}
		if(sz(q) > 7){
			auto u = q.front(); q.pop();
			for(auto w : u){
				ss.erase({-freq[w.first] , w.first});
				freq[w.first] -= w.second;
				if(freq[w.first]) ss.insert({-freq[w.first] , w.first});
			}	
		}
	}	
}
