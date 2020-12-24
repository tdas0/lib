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

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int test;
	cin>>test;
	while(test--){
		int n, m;
		string s;
		cin>>n>>m;
		cin>>s;		
		int qtd=0;
		bool solved=0;
		for(int i=0;i<n;i++) if(s[i]=='0') qtd ++;
		for(int x=0;x<=n;x++){
			if(solved) break;
			int total = x*m - qtd;
			if(total < 0) continue;
			vector<int> cost(n);
			int can=1;
			for(int j = 0;j<n;j++){
				int aguenta=x;
				if(s[j] == '0'){
					aguenta --;
				}
				cost[j]=min(2*(aguenta/2), 2*(total/2));
				total -= cost[j];
			}
			if(!total){
				// cout<<"porra   "<<x<<"\n";
				vector< vector<int> > ans;
				ans.resize(x);
				for(int i = 0; i < x; i++) ans[i].resize(n);
				vector<int> qtd(x);
				int can=1;
				for(int j = 0; j < n; j++){
					int curr = cost[j] + (s[j]=='0');
					// cout<<"precisa "<<j<<" "<<curr<<"\n";
					vector<pii> caras;
					for(int h = 0;h<x;h++)caras.pb({qtd[h], h});
					sort(all(caras));
					for(auto pp:caras){
						int h=pp.s;
						if(qtd[h] < m and curr){
							qtd[h] ++;
							ans[h][j]=1;
							curr--;
						}
					}
					if(curr){
						can=0;
						// cout<<"poooor "<<j<<" "<<curr<<"\n";
					}
				}
				for(int i = 0; i < x; i++){
					int qtd=0;
					for(int j = 0; j < n; j++){
						if(ans[i][j] == 1) qtd ++;
					}
					if(qtd != m){
						can=0;
						//cout<<"POOOOO\n";
					}
				}
				if(can){
					cout<<x<<"\n";
					for(int i = 0; i < x; i++){
						for(int j=0;j<n;j++) cout<<ans[i][j];
						cout<<"\n";
					}
					solved=1;
					break;
				}
			}
		}
		if(!solved){
			cout<<"CATACLYSM IMMINENT - TIME TO HOARD FACE MASKS\n";
		}
	}
}