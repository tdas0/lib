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

const int N = 301005;
int a[N] , n;
int BIT[N];
void upd(int x,int v){
	while(x<N){
		BIT[x]+=v;
		x+=(x&-x);
	}
}
int sum(int x){
	int r=0;
	while(x>0){
		r+=BIT[x];
		x-=(x&-x);
	}
	return r;
}

int query(int l,int r){
	return sum(r) - sum(l-1);
}

const int M = 998244353;
ll pwr[N];
int l[N],r[N],x[N];

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;
	pwr[0] = 1;
	rep(i,1,N)pwr[i] = (pwr[i-1]*2ll)%M;
	cin >> n >> m;
	vi vec;
	for(int i=0;i<n;i++){
		cin >> l[i] >> r[i];
		vec.pb(l[i]);vec.pb(r[i]);
	}
	for(int i=0;i<m;i++){
		cin >> x[i];
		vec.pb(x[i]);
	}
	sort(all(vec));;
	vec.erase(unique(all(vec)),vec.end());
	sort(x,x+m);
	ll res=0;
	int pt=0;
	vector<pii> v;
	vector<pii> ev;
	for(int i=0;i<n;i++){
		l[i] = lower_bound(all(vec),l[i])-vec.begin() + 1;
		r[i] = lower_bound(all(vec),r[i])-vec.begin() + 1;
		v.pb(pii(l[i],r[i]));
		ev.pb(pii(l[i],1));
		ev.pb(pii(r[i]+1,-1));
	}
	sort(all(v));
	sort(all(ev));
	int pt1=0;
	int open=0;

	for(int i=0;i<m;i++){
		x[i] = lower_bound(all(vec),x[i])-vec.begin() + 1;

		while(pt1 < sz(ev) and ev[pt1].ff <= x[i]){
			open+=ev[pt1].ss;
			pt1++;
		}

		while(i>0 and pt < m and v[pt].ff <= x[i-1]){
			int R = v[pt].ss;
			upd(R,+1);
			pt++;	
		}
		int mine = open;
		int last = query(x[i],N-1);

		res = (res + pwr[mine] - pwr[last] + M + M)%M;
		
	}
	res%=M;
	if(res<0)res+=M;
	cout << res << endl;
}
