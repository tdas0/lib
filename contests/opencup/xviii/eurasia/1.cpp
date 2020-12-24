#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define pb push_back
#define all(x) begin(x), end(x)


using namespace std;
char gett(int x){
	if(x <= 9) return (x + '0');
	char L = 'A';
	for(int d = 10; d <= 16; d++){
		if(x == d) return L;
		L++;
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	ifstream cin("input.txt");
 ofstream cout("output.txt");
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		string ans = "";
		vector<char> caras;
		for(int i = sz(s) - 1; i >= 0; i--){
			caras.pb(s[i]);
			if(sz(caras) == 4){
				int val = 0;
				// reverse(all(caras));
				//for(auto w: caras) cout<<w<<" ";
				//cout<<"\n";
				for(int j = 0; j < sz(caras); j++){
					if(caras[j] == '1'){
						val += (1<<j);
						//cout<<"bit "<<j<<"\n";
					}
				}
				char cara = gett(val);
				// cout<<"vak = "<<val<<" "<<cara<<"\n";
				ans.pb(cara);
				caras.clear();
			}
		}
	int val = 0;
	//reverse(all(caras));
	if(sz(caras) != 0){
		for(int j = 0; j < sz(caras); j++){
			if(caras[j] == '1'){
				val += (1<<j);
			}
		}
		char cara = gett(val);
		caras.clear();
		ans.pb(cara);
	}
		int len = (sz(s) % 4 == 0 ? (sz(s)/4) : sz(s)/4 + 1);
		while(sz(ans) < len)ans.pb('0');
		for(int j = sz(ans) - 1; j >= 0; j--) cout<<ans[j];
		cout<<"\n";
	}
}