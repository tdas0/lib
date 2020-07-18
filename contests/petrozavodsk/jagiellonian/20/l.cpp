#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
#define N 300050

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q;
	cin>>q;
	while(q--){
		int n, k;
		cin>>n>>k;
		vector<int> t(n);
		int ans = 0;
		priority_queue<int, vector<int>, greater<int> > pq;
		for(int i=0;i<n;i++){
			cin>>t[i];
			pq.push(t[i]);
		}
		sort(all(t));
		reverse(all(t));
		for(int i =0;i<k;i++) ans =max(ans, t[i]);
		int curr=0;
		for(int j = k;j<n;j++) curr += t[j];
		cout<<max(curr, ans)<<"\n";
	}
}
