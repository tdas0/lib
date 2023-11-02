// coded pos contest by naimss
// O(N log^2)
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define pb push_back
#define ff first
#define ss second
#define endl '\n'
#define sz(v) ((int)v.size())
#define all(v) begin(v),end(v)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;


const int N = 200100;
int s[N], p[N];
ll resp[N];
pii B[N];


ll cost(pii a,pii b){
	if(b.ss < a.ss)return 0;
	return 1ll * (b.ff - a.ff) * (b.ss - a.ss);
}

// cost = (B.ff - A.ff) * (B.ss - A.ss);

void dnc(
	vector<ll> &ans,
	vector<pii> &a,vector<pii>&b,int la,int ra,int lb,int rb){
	if(la > ra || lb > rb)return ;
	int m = (la + ra)/2;
	int optB = lb;
	for(int i=lb + 1;i<=rb;i++){
		if(cost(a[m], b[optB]) < cost(a[m], b[i]))
			optB = i;
	}
	ans[m] = cost(a[m], b[optB]);
	dnc(ans,a,b,la,m-1,lb,optB),
	dnc(ans,a,b,m+1,ra,optB,rb);
}

void solve(vector<array<int,3> > A,vector<pii> B){
	if(sz(A) == 0)return ;
	else if(sz(B)==0)return ;
	sort(all(A));
	// A[1].ff < A[2].ff ...
	// A[1].ss > A[2].ss ...
	vi idA; idA.pb({A[0][2]});
	vector<pii> nA;nA.pb(pii(A[0][0], A[0][1]));
	for(auto [p,d,id] : A){
		if(p == nA.back().ff)
			continue;
		if(d < nA.back().ss){
			nA.pb(pii(p,d));
		}
	}
	sort(all(B),[&](pii a,pii b){
		if(a.ff != b.ff)return a.ff > b.ff;
		return a.ss > b.ss;
	});
	// B[1].ff > B[2].ff > ...
	// B[1].ss < B[2].ss  ...
	vector<pii> nB; nB.pb(B[0]);
	for(auto it : B){
		if(it.ff == nB.back().ff)continue;
		if(it.ss > nB.back().ss)
			nB.pb(it);
	}
	reverse(all(nB));
	vector<ll> ans(sz(nA));
	dnc(ans,nA,nB,0,sz(nA)-1,0,sz(nB)-1);
	int pt=0;

	for(int i=0;i<sz(A);){
		while(i < sz(A) && pii(A[i][0],A[i][1]) == nA[pt]){
			int id = A[i][2];
			resp[id] = max(resp[id], ans[pt]);
			i++;
		}
		pt++;
	}
	return ;
}

void solve(int l,int r,vector<array<int,4>> &question){
	vector<array<int,4>> ql,qr,qHere;
	int m = (l+r)/2;
	for(auto [a,b,id,iq] : question){
		if(a == l && b == r){
			qHere.pb({a,b,id,iq});
		}
		else if(b <= m)ql.pb({a,b,id,iq});
		else if(a > m)qr.pb({a,b,id,iq});
		else if(a<=m && b > m){
			ql.pb({a,m,id,iq}),qr.pb({m+1,b,id,iq});
		}
	}
	vector<array<int,3>> A;
	vector<pii> BB;
	for(auto [a,b,id,iq] : qHere)
		A.pb({s[id], p[id], iq});
	for(int i=l;i<=r;i++)if( B[i].ff )BB.pb(B[i]);
	solve(A, BB);
	if( l == r )return;
	solve(l,m,ql),solve(m+1,r,qr);
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	rep(i,1,n+1){
		cin >> s[i] >> p[i];
		--s[i];
	}
	int q;
	cin >> q;
	vector<array<int,4>> question;
	rep(i,1,q+1){
		char ch;
		cin >> ch;
		if(ch == 's'){
			int id;
			cin >> id;
			question.pb({1,i,id,i});
			B[i] = pii(0,0);
		}else{
			int e,r;cin >> e >> r;
			B[i] = pii(e,r);
		}
	}
	solve(1,q,question);
	rep(i,1,q+1)if(!B[i].ff)cout << resp[i] << endl;
}
