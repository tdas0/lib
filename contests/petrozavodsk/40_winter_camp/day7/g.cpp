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

const int N = 200100;
const int M = 998244353;

ll qtd[5][5];
ll dp[N][5];

int calc(string s,string t){
	int n = sz(s);
	int m = sz(t);
	rep(i,0,N)rep(j,0,m+1)dp[i][j]=0;
	dp[n][m] = 1;
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<=m;j++){
			dp[i][j] = (dp[i+1][j]);
			if(j!=m and s[i] == t[j]){
				dp[i][j]+=dp[i+1][j+1];
				if(dp[i][j]>=M)dp[i][j]-=M;
			}
		}
	}

	return dp[0][0];
}

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,k;
	cin >> n >> k;
	string s;
	cin >> s;
	string t = "";
	for(auto it : s){
		if(it=='W' || it=='A' || it=='C')t+=it;
	}
	s = t;

	string pat = "WAC";

	rep(i,0,3){
		string cur="";
		rep(j,i+1,4){
			cur+=pat[j-1];
			qtd[i][j]= calc(s,cur);
		}
	}
	rep(i,0,N)rep(j,0,4)dp[i][j]=0;
	dp[k][3] = 1;
	for(int i=k-1;i>=0;i--){
		for(int j=0;j<=3;j++){
			dp[i][j] = dp[i+1][j];
			for(int p2=j+1;p2<=3;p2++){
				dp[i][j] = (dp[i][j] + 1ll*dp[i+1][p2]*qtd[j][p2]%M)%M;
			}
		}
	}
	cout << dp[0][0] << endl;
}
