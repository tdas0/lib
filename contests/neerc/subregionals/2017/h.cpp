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
#define div oasjdasid
int n;
string s;
vi div;

void check(int x){
	map<char,int> cnt;
	for(auto w : s){
		cnt[w] ++ ;
	}
	if((n/x)%2 == 0){
		bool ok = true;
		for(auto w : cnt)
			if(w.S & 1)
				ok = false;
		if(ok){
			deque<char> ans;
			for(auto w : cnt){
				int ha = w.S;
				while(ha > 0){
					ans.push_back(w.F);
					ans.push_front(w.F);
					ha -= 2;
				}
			}
			cout << 1 << endl;
			for(auto w : ans){
				cout << w;
			}
			cout << endl;
			exit(0);
		}		
	}
	else{
		vector<deque<char> > v(x);
		int curptr = 0;
		for(char a = (char) 0 ; a < CHAR_MAX ; a++){
			if(cnt.count(a)){
				if(cnt[a]&1){
					if(curptr < sz(v)){
						v[curptr].push_back(a);
						cnt[a] --;
						curptr++;
					}
					else{
						return ;
					}
				}
			}
		}
		for(char a = (char) 0 ; a < CHAR_MAX  ; a ++){
			if(cnt.count(a)){
				while(curptr + 1 < sz(v) && cnt[a] >= 2){
						v[curptr].push_back(a);
						cnt[a] -- ;
						curptr++;
						v[curptr].push_back(a);
						cnt[a] -- ;
						curptr++;						
				}
			}
		}
		if(curptr != sz(v))
			return ;
		for(auto &w : v){
			while(sz(w) != n/x){
				for(char a = (char) 0 ; a < CHAR_MAX  ; a++){
					if(cnt[a] >= 2){
						w.push_back(a);
						w.push_front(a);
						cnt[a] -= 2;
						break;
					}
				}
			}
		}
		cout << x << endl;
		for(auto w : v){
			for(auto k : w){
				cout << k;
			}
			cout << " ";
		}
		cout << endl;
		exit(0);
	}
}

int32_t main(){
	cin >> n >> s;
	for(int i = 1; i <= n; i ++){
		if(n%i == 0)
			div.push_back(i);
	}
	for(auto w : div){
		check(w);
	}
}
