#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int) (x).size()
const int N = 200005;
typedef long long ll;
typedef vector<int> vi;
int n;
ll a[N] ; 
pair< ll , int > b[N];

struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		for(int i =0 ; i < n+1 ; i ++) p[i] = i;
	}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};	

int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++){
		scanf("%lld" , &a[i]);
		b[i] = {a[i] , i};
	}
	sort(b+1,b+1+n);
	ll l = 0 , r = (ll) 1e18;
	ll ans = 0;
	while(l<=r){
		ll mid = l + (r-l)/2;
		dsu T(n);
		bool ok = true;
		vector<int> F , S;
		for(int i = 1; i < n; i ++){
			if(abs(b[i].first - b[i+1].first) <= mid)
				T.join(b[i].second,  b[i+1].second);
		}
		for(int i = 1; i <= n; i ++){
			if(T.find(i) != T.find(b[i].second)){
				ok = false;
			}
		}
		if(ok){
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	printf("%lld\n" , ans);
}
