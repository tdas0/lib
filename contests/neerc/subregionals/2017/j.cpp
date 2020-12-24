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
const int N = 100005;
ll a[N], b[N], p[N], suf[N];
int n , m;
vi good[N];
int st[4*N];

void build(int l = 1, int r = n , int curr = 1){
	int mid = l +(r-l)/2;
	if(l == r){
		st[curr] = a[l];
		return ;
	}
	build(l,mid,2*curr);
	build(mid+1,r,2*curr+1);
	st[curr] = max(st[2*curr] , st[2*curr+1]);
}

int find(int x , int l = 1, int r = n,  int curr =1){
	int mid = l + (r-l)/2;
	if(l == r){
		return l;
	}
	if(st[2*curr + 1] >= x){
		return find(x,mid+1,r,2*curr+1);
	}
	else if(st[2*curr] >= x)
		return find(x,l,mid,2*curr);
	return n+1;
}

int32_t main(){
	scanf("%d%d" , &n , &m);
	for(int i = 1; i <= n; i ++){
		scanf("%lld" , &a[i]);
	}
	build();
	for(int i = 1 ; i<= m; i ++){
		scanf("%lld" , &b[i]);
		int L = 1 , R = n;
		int ans = find(b[i]);
		good[ans].push_back(i);
	}
	for(int i = 1; i <= m; i ++){
		scanf("%lld" , &p[i]);
	}
	priority_queue<ll> pq;
	ll cur = 0;
	for(int i = 1; i <= n; i++){
		priority_queue<ll , vector<ll> , greater<ll> > curr;
		for(auto w : good[i])
			curr.push(p[w]);
		cur += 1ll*a[i];
		while((sz(curr) && sz(pq) && pq.top() > curr.top()) || (sz(curr) && curr.top() <= cur)){
			if(sz(curr) && curr.top() <= cur){
				pq.push(curr.top());
				cur -= curr.top();
				curr.pop();
			}
			else{
				cur += pq.top();
				pq.pop();
				cur -= curr.top();
				pq.push(curr.top());
				curr.pop();
			}
		}
	}
	printf("%d\n" , sz(pq));
}
