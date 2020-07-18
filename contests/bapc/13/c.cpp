#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
#define N 300050

string s[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q, n;
	cin>>q;
	while(q--){
		string x, d;
		cin>>n;
		for(int i = 1; i<=n;i++){
			cin>>s[i];
		}
		cin>>d;
		cin>>x;
		vector<int> caras;
		map<pair<char, char>, int> key;
		set<char>forb;
		int qtd=0;
		for(int i=1;i<=n;i++){
			// cout<<"porra "<<i<<"\n";
			map<char, char> par;
			map<char, char> rev;
			bool can=true;
			string A = s[i], B=d;
			if(sz(A) != sz(B)) continue;
			for(int j =0;j<min(sz(A),sz(B)); j++){
				if(par.count(A[j]) and !rev.count(B[j])) can = false;
				else if(!par.count(A[j]) and rev.count(B[j])) can = false;
				if(par.count(A[j]) and rev.count(B[j])){
					if(par[A[j]] != B[j] or rev[B[j]] != A[j]) can = false;
				}
				else{
					par[A[j]] = B[j];
					rev[B[j]] =A[j];
				}
				if(!can){
					// cout<<"merda "<<j<<"\n";
					break;
				}
			}
			if(can){
				qtd++;
				// cout<<"good "<<i<<"\n";
				for(char c='a';c <= 'z'; c++){
					if(!par.count(c)) continue;
					key[{c, par[c]}] ++;
				}
			}
		}
			if(!qtd){
				cout<<"IMPOSSIBLE\n";
			}
			else{
				set<char>livres, livres2;
				for(char c='a';c<='z';c++) livres.insert(c), livres2.insert(c);
				map<char, char> fim;
				for(char a='a';a<='z';a++){
					for(char b='a';b<='z';b++){
						if(key[{a, b}] == qtd){
							fim[a]=b;
							livres.erase(a);
							livres2.erase(b);
						}
					}
				}
				if(sz(livres2) == 1 and sz(livres) == 1){
					fim[*livres.begin()] = *livres2.begin();
					// cout<<"cacete\n";
				}
				for(int i=0;i<sz(x);i++){
					if(fim.count(x[i])){
						cout<<fim[x[i]];
					}
					else cout<<"?";
				}
				cout<<"\n";
			}
	}
}
