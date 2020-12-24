#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define sz(x) (int)(x).size()
typedef vector<string> vs;
int t;
int curr = 0 ;
const int N = 100005;
int trie[N*27]; 
char child[N*27]; 
bool can = false;
int ans = 0;

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	cin >> t;
	while(t--){
		int n ;
		cin >> n;
		can = true;
		ans = 0;
		curr = 0 ;
		rep(i,0,n){
			string s;
			cin >> s;
			int atual = 0;
			rep(j,0,sz(s)){
				if(trie[atual]){
					if(child[atual] != s[j]){
						can = false;
						break ; 
					}
				}
				else{
					trie[atual] = ++curr;
					ans ++ ;
					child[atual] = s[j]; 
				}
				atual = trie[atual];
			}
		}
		rep(i,0,curr+1){
			trie[i] = 0;
			child[i] = 0;
		}
		if(can) cout << ans << endl;
		else cout << "Impossible" << endl;
	}
}	