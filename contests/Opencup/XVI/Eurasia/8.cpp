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

int n, s;
pii w[N];
// int solve(int i, int S, int flag){
// 	if(i > n){
// 		if(S == s) return 0;
// 		return -20000000;
// 	}
// 	if(w[i].f != w[i+1].f){
// 		int A = solve(i + 1, S + w[i].s, 1) + flag;
// 		int B = solve(i + 1, S, 1);
// 		return max(A, B);
// 	}
// 	else{
// 		int A = solve(i + 1, S + w[i].s, 0) + flag;
// 		int B = solve(i + 1, S, flag);
// 		return max(A, B);
// 	}
// }
int dp[2][50050][2];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>s;
	for(int i = 1; i <= n; i++){
		cin>>w[i].f>>w[i].s;
	}
	sort(w+1,w+n+1);
	#define inf 2000000
	for(int i=n+1;i>=1;i--){
		for(int S = s; S >= 0; S--){
			for(int flag = 0; flag < 2; flag ++){
				if(i > n){
					if(S == s)dp[i&1][S][flag] = 0;
					else dp[i&1][S][flag] = -inf;
				}
				else{
					if(w[i].f != w[i + 1].f){
						int A = (S + w[i].s <= s ? dp[(i+1)&1][S + w[i].s][1] + flag : -inf);
						int B = dp[(i+1)&1][S][1];
						dp[i&1][S][flag] = max(A, B);
					}
					else{
						int A = (S+w[i].s <= s? dp[(i+1)&1][S +w[i].s][0]+flag : -inf);
						int B=dp[(i+1)&1][S][flag];
						dp[i&1][S][flag]=max(A, B);
					}
				}
			}
		}
	}
	if(dp[1][0][1] < 0) cout<<"Impossible\n";
	else cout<<dp[1][0][1]<<"\n";
}
