#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()
#define ff first
#define ss second
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef vector<int> vi;

int val(char c){
	if(c == 'R')return 0;
	if(c=='B')return 1;
	return 2;
}



pii cur[3];


void solve(){
	int A,B,C;
	vi v(3);
	rep(i,0,3)cin >> v[i];
	sort(all(v),greater<int>());

	A = v[0],B = v[1],C = v[2];
	// B+C >= 43

	vi cnt(3,0);
	vi fixed(3,0);

	cur[1] = pii(0,0); // (qtd,tipo)
	cur[2] = pii(0,1);



	int foi = 0;

	if(B + C >= 43 ){
		rep(iter,0,100){

			char ch;
			cin >> ch;
			int x = val(ch);
			if(x==0){
				cout<<"DISCARD"<<endl;
			}else cout<<"PLACE "<<x<<endl;

			cout.flush();
		}
		return;
	}

	if(A - B + B - C >= 43){ // A - C + B - C
		
		rep(iter,0,100){

			char ch;
			cin >> ch;
			int x = val(ch);
			cnt[x]++;
			int flag=0;
			for(int i=1;i<=2;i++){
				if(cur[i].ss == x){
					cur[i].ff++;
					flag = 1;
					if(cnt[x] > C)fixed[x] = 1;
					cout << "PLACE "<<i<<endl;
					break;
				}
			}
			if(flag)continue;

			if(fixed[ x ]){
				if(cur[1].ss == x){
					cur[1].ff++;
					cout << "PLACE 1"<<endl;
				}else{
					cur[2].ff++;
					cout << "PLACE 2"<<endl;
				}
			}else{
				if(cnt[x] > C){
					for(int i=1;i<=2;i++){
						if(!fixed[cur[i].ss]){
							cout<<"EMPTY "<<i<<endl;
							cout<<"PLACE "<<i<<endl;
							cur[i].ff = 1;
							cur[i].ss = x;
							break;
						}
					}
					fixed[x] = 1;
				}else{
					cout<<"DISCARD"<<endl;
				}
			}


			cout.flush();
		}

	}else{

		// A - B + C
		assert(A - B + C >= 43);


		rep(iter,0,100){

			char ch;
			cin >> ch;
			int x = val(ch);
			cnt[x]++;
			int flag=0;
			for(int i=1;i<=2;i++){
				if(cur[i].ss == x){
					cur[i].ff++;
					flag = 1;
					if(cnt[x] > B)fixed[x] = 1;
					cout << "PLACE "<<i<<endl;
					break;
				}
			}
			if(flag)continue;

			if(fixed[ x ]){
				if(cur[1].ss == x){
					cur[1].ff++;
					cout << "PLACE 1"<<endl;
				}else{
					cur[2].ff++;
					cout << "PLACE 2"<<endl;
				}
			}else{
				if(cnt[x] > B){
					for(int i=1;i<=2;i++){
						if(!fixed[cur[i].ss]){
							cout<<"EMPTY "<<i<<endl;
							cout<<"PLACE "<<i<<endl;
							cur[i].ff = 1;
							cur[i].ss = x;
							break;
						}
					}
					fixed[x] = 1;
				}else{
					cout<<"DISCARD"<<endl;
				}
			}


			cout.flush();
		}



	}



}


int32_t main(){
	//ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}
