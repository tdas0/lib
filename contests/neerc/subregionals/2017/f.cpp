#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;


int32_t main(){
	int n;
	cin >> n;
	set<deque<char> > s;
	for(int i = 0  ; i < n ; i ++){
		string x;
		cin >> x;
		deque<char> p;
		for(int i = 0 ; i < sz(x) ; i ++){
			if(x[i] == 'u'){
				p.push_back('o') , p.push_back('o');
				continue;
			}
			while(p.size() && x[i] == 'h' && p.back() == 'k'){
				p.pop_back();
			}
			p.push_back(x[i]);
		}
		s.insert(p);
	}
	cout << sz(s);
}
