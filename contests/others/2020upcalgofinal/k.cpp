#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 300050
typedef pair<int, int> pii;
#define f first
#define s second
int n;
pii w[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>w[i].s;
	for(int i = 1; i <= n; i++) cin>>w[i].f;
		sort(w+1, w+n+1);
	for(int i = 1;i<=n;i++) cout<<w[i].s<<" \n"[i==n];
}
