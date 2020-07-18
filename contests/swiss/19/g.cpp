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
#define N 34

int n, k, v[N];
int dp[2][N][101][N][101], tot,pref[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>k;
	for(int i = 1; i <= n; i++) cin>>v[i], tot += v[i],pref[i]=pref[i-1]+v[i];
	dp[0][0][0][0][0] = 1;
	pair<ll, ll> curr = {-1,-1}, T;
	for(int i = 1; i <= n; i++){
		for(int sum1 = 0; sum1 <= 100; sum1 ++){
			for(int sum2 = 0; sum2 <= 100; sum2 ++){
				for(int q1 = 0; q1 <= i; q1++){
					for(int q2 = 0; q2 <= i; q2++){
						int q3 = (i-q1-q2), sum3 = pref[i]-sum1-sum2;
						if(q3<0 or sum3 < 0){
							dp[i&1][q1][sum1][q2][sum2] = 0;
							continue;
						}
						int A = (q1 >= 1 and sum1 >= v[i]) ? dp[(i-1)&1][q1 - 1][sum1 - v[i]][q2][sum2]:0;
						int B = (q2 >= 1 and sum2 >= v[i]) ? dp[(i-1)&1][q1][sum1][q2-1][sum2-v[i]]:0;
						int C = (q3 >= 1 and sum3 >= v[i])?dp[(i-1)&1][q1][sum1][q2][sum2]:0;
						dp[i&1][q1][sum1][q2][sum2] = min(1, A+B+C);
						if(i == n and A+B+C>=1 and q1 > 0 and q2>0 and q3>0){
							ll p = (1LL*sum1*q2*q3) + 1LL*sum2*q1*q3 + 1LL*sum3*q1*q2;
							ll q = 3LL*q1*q2*q3;
							ll d = __gcd(p, q);
							p/=d;
							q/=d;
							// if(p==137)
							// cout<<p<<"/"<<q<<"\n";
							ll A = abs(p-q*k);
							if(curr.f == -1 or A * curr.s < q*curr.f){
								curr.f = abs(p-q*k);
								curr.s = q;
								T = {p,q};
							}
						}
					}
				}
			}
		}
	}

	cout<<T.f<<"/"<<T.s<<"\n";
}
