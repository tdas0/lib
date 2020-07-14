#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
#define N 300050
vector<int> T[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int n, k, sum = 0;
	cin>>n>>k;
	vector<int>v(n);
	for(int i=0;i<n;i++){
		int a, b;
		cin>>a>>b;
		T[a].pb(b);
	}
	vector<int> ans;
	for(int i=1;i< N; i++){
		sort(T[i].begin(), T[i].end());
		if(!T[i].empty()) ans.push_back(T[i][0]);
	}
	int resp = 0;
	sort(ans.begin(), ans.end());
	for(int i = 0; i < (int)ans.size(); i++){
		sum += ans[i];
		if(sum <= k){
			resp ++;
		}
	}
	cout<<resp<<"\n";
}
