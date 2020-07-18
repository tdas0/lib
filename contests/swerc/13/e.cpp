#include <algorithm>
#include <iostream>
#include <assert.h>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <bitset>
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
int n  , z= 0 ;
string s , s2; 
char transform(char p){
	if('a' <= p && p <= 'z') return p;
	if('A' <= p && p <= 'Z') return p - 'A' + 'a';
	return '.';
}


void ask(vs c){
	cout << (sz(c) == 1 ? "What does the word ": "What does the sentence ")  << "\"" ; 
	bool jf = false;
	for(auto w : c){
		if(jf) cout <<" ";
		cout << w ;
		jf = true;
	}
	cout<< "\" mean?" << endl;   
}

int32_t main(){
	while(cin >> n){
		cout << "Learning case "<< ++z << endl;
		set<vs> dir;
		dir.insert({"joe"});
		vs opt;
		vs opt2;
		while(cin >> s && s != "*"){
			for(auto &w : s){
				w = transform(w);
			}	
			if(s == "."){
				for(int len = 1; len <= n; len ++){
					for(int j = 0 ; j < sz(opt) - len + 1;  j++){
						vs curr;
						for(int i = 0 ; i < len ; i ++){
							curr.push_back(opt[j + i]);
						}
						dir.insert(curr);
					}
				}
				opt.clear();
			}
			else
				opt.push_back(s);
		}	
		if(sz(opt)){
			for(int len = 1; len <= n; len ++){
				for(int j = 0 ; j < sz(opt) - len + 1;  j++){
					vs curr;
					for(int i = 0 ; i < len ; i ++){
						curr.push_back(opt[j + i]);
					}
					dir.insert(curr);
				}
			}
			opt.clear();
		}
		while(cin >> s && s != "#"){
			s2 = s;
			for(auto &w : s){
				w = transform(w);
			}
			if(s == "."){
				int jj = 0;
				for(auto w : opt){
					if(!dir.count({w})){
						ask({opt2[jj]});
						dir.insert({w});
					}
					jj++;
				}
				bool ok = true;
				for(int len = 2 ; len <= n ; len++){
					for(int j = 0 ; j < sz(opt) - len + 1 ; j ++){
						vs curr;
						for(int i = 0 ; i < len ; i ++){
							curr.push_back(opt[j + i]);
						}
						if(!dir.count(curr)){
							ok = false;
							break;
						}
					}
					if(!ok) break;
				}
				if(!ok) ask(opt2);
				for(int len = 1; len <= n; len ++){
					for(int j = 0 ; j < sz(opt) - len + 1;  j++){
						vs curr;
						for(int i = 0 ; i < len ; i ++){
							curr.push_back(opt[j + i]);
						}
						dir.insert(curr);
					}
				}
				opt.clear() , opt2.clear();
			}
			else opt.push_back(s) , opt2.push_back(s2);
		}
		if(sz(opt)){
				int jj = 0;
				for(auto w : opt){
					if(!dir.count({w})){
						ask({opt2[jj]});
						dir.insert({w});
					}
					jj++;
				}
				bool ok = true;
				for(int len = 2 ; len <= n ; len++){
					for(int j = 0 ; j < sz(opt) - len + 1 ; j ++){
						vs curr;
						for(int i = 0 ; i < len ; i ++){
							curr.push_back(opt[j + i]);
						}
						if(!dir.count(curr)){
							ok = false;
							break;
						}
					}
					if(!ok) break;
				}
				if(!ok) ask(opt2);
				for(int len = 1; len <= n; len ++){
					for(int j = 0 ; j < sz(opt) - len + 1;  j++){
						vs curr;
						for(int i = 0 ; i < len ; i ++){
							curr.push_back(opt[j + i]);
						}
						dir.insert(curr);
					}
				}
				opt.clear() , opt2.clear();			
		}		
		cout << endl;
	}
}