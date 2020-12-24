#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int32_t main(){
	ll n , a , b;
	cin >> n >> a >> b;
	ll ans = 2*n;
	for(ll i = 0 ; i <= n; i ++){
		for(ll j = 0 ; j <= n ; j ++){
			if((a*i + j*b) >= n && (a*i + j*b)%n == 0){
				ans = min(ans , i+j);
			}
		}
	}
	cout << ans << endl;
}