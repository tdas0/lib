#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define endl '\n'
#define pb push_back


const int N = 6e4 + 100;

double tree[N*4];
double lazy[4*N];
bool la[N*4];

int P[N];


void build(int No,int i,int j){
	for(int no = 0;no<=4*j+10;no++){
		tree[no] = lazy[no] = la[no] = 0;
	}
}

void flush(int no,int i,int j){
	if(la[no]){
		tree[no]+=lazy[no];

		int mid = (i+j)/2,l=no*2,r=no*2+1;
		if(i!=j){
			la[l] = la[r] = 1;
			lazy[l]+=lazy[no];
			lazy[r]+=lazy[no];
		}	
		la[no] = 0;
		lazy[no] = 0;
	}
}

void upd(int no,int i,int j,int a,int b,double val){
	flush(no,i,j);
	if(i > j or i > b or j < a)return;
	if(a<=i and j<=b){
		la[no] = 1;
		lazy[no]+=val;
		flush(no,i,j);
		return;
	}

	int mid = (i+j)/2,l=no*2,r=no*2+1;
	upd(l,i,mid,a,b,val);
	upd(r,mid+1,j,a,b,val);
	tree[no] = min(tree[l],tree[r]);
}
const double inf = 1e18;
double query(int no,int i,int j,int a,int b){
	flush(no,i,j);
	if(i > j or i > b or j < a)return inf;
	if(a<=i and j<=b)return tree[no];
	int mid = (i+j)/2,l=no*2,r=no*2+1;
	return min(query(l,i,mid,a,b),query(r,mid+1,j,a,b));
}
int a[N];
vi pos[N];
const double EPS = 1e-9;
int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		pos[a[i]].pb(i);
	}
	double L = 0,R = 1;
	double ans = 1;
	
	for(int iter=0;iter<20;iter++){
		double mid = (L+R)/2.0;
		build(1,1,n);
			
		for(int i=1;i<=n;i++){
			upd(1,1,n,i,i,- 1.0 * mid * i);
			P[i] = 0;
		}

		for(int i=1;i<=n;i++){
			if(sz(pos[i]) > 0){
				upd(1,1,n,pos[i][0],n,+1);
				P[i] = 0;
			}
		}

		bool ok = 0;
		for(int i=1;i<=n;i++){
			if(i > 1){
				// tira de antes:
				upd(1,1,n,pos[a[i-1]][P[a[i-1]]],n,-1);
				P[a[i-1]]++;
				if(P[a[i-1]]<sz(pos[a[i-1]])){
					upd(1,1,n,pos[a[i-1]][P[a[i-1]]],n,+1);
				}
			}
			
			double cur = query(1,1,n,i,n);
		
			if(cur - EPS <= mid - mid * i){
				ok = 1;
				break;
			}
		}

		
		if(ok){
			ans = mid;
			R = mid;
		}else L = mid;

	}
	cout << setprecision(10) << fixed;
	cout << ans << endl;
}
