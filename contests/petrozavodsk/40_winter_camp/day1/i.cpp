#include <bits/stdc++.h>
#define N 2000010
using namespace std;
typedef long long ll;
int n, cnt[N];
ll ans;
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int test;
	cin>>test;
	while(test--){
		ans = 0;
		cin>>n;
		const int MX = 1000005;
		for(int i = 0; i <= MX; i++) cnt[i] = 0;
		for(int i = 1, x; i <= n; i++) cin>>x, cnt[x] ++;
		for(int x = 1; x <= MX; x++){
			for(int i = x; i <= MX; i += x){
				int j = (x^i);
				if(j < MX and __gcd(i, j) == x)ans += (1LL*cnt[j]*cnt[i]);
			}
		}
		cout<<ans/2LL<<"\n";
	}
}
