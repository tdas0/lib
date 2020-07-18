#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
#define ff first
#define ss second
#define pb push_back
typedef vector<int> vi;
#define int long long

ll MOD = (1LL<<32);

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

ll rev_sum(ll H,int shift,bool mod){
	if(mod)return -1;
	ll d = (1LL<<shift);
	ll inv = (inverse<ll>(d+1,MOD) + MOD)%MOD;
	//cout << d+1<<" "<<inv << endl;
	H%=MOD;
	H = (H * inv)%MOD;
	if(H<0)H+=MOD;
	return H;
}

ll rev_xor(ll H,int shift,bool mod){
	ll d = (1LL<<shift);
	ll res = 0;
	for(int i=0;i<shift;i++){
		if((1LL<<(31LL - i))&H){
			res|=(1LL<<(31LL - i));
		}
	}
	for(int pos = shift;pos<32;pos++){
		ll cur = (H&(1LL<<(31LL - pos)));
		ll cur2 = (res&(1LL<<(31LL - (pos - shift))));
		if(cur){
			if(cur2==0)res|=(1LL<<(31LL - pos));
		}
		if(cur==0){
			if(cur2)res|=(1LL<<(31LL - pos));
		}
	}

	if(res < 0)return -1;
	if((res^(res/d))%MOD == H)return res;
	return -1;

}

void solve(){
	ll H;
	cin>>H;
	set<ll> cur;
	cur.insert(H);

	set<ll> nv;
	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		ll val = rev_sum(*it,16,0);
		ll val2 = rev_sum(*it,16,1);
	//	cout << val <<" "<<val2 << endl;
		if(val!=-1)nv.insert(val);
		if(val2!=-1)nv.insert(val2);
	}
	cur.clear();
	cur = nv;
	nv.clear();


	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		ll val = rev_xor(*it,11,0);
		ll val2 = rev_xor(*it,11,1);
	//	cout << val<<" "<<val2 << endl;
		if(val!=-1)nv.insert(val);
		if(val2!=-1)nv.insert(val2);
	}

	cur.clear();
	cur = nv;
	nv.clear();
	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		ll val = rev_sum(*it,3,0);
		ll val2 = rev_sum(*it,3,1);
	//	cout <<"sum "<< val<<" "<<val2 << " " << *it << endl;
		if(val!=-1)nv.insert(val);
		if(val2!=-1)nv.insert(val2);
	}

	cur.clear();
	cur = nv;
	nv.clear();
	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		ll val = rev_xor(*it,6,0);
		ll val2 = rev_xor(*it,6,1);

	//	cout <<"xor "<< val<<" "<<val2 << endl;

		if(val!=-1)nv.insert(val);
		if(val2!=-1)nv.insert(val2);
	}

	cur.clear();
	cur = nv;
	nv.clear();
	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		ll val = rev_sum(*it,10,0);
		ll val2 = rev_sum(*it,10,1);
    //	cout << val<<" "<<val2 << endl;
		if(val!=-1)nv.insert(val);
		if(val2!=-1)nv.insert(val2);
	}


	cur.clear();
	cur = nv;
	nv.clear();

	for(set<int>::iterator it = cur.begin();it!=cur.end();it++){
		if(*it < MOD){
			cout << *it << endl;
			return;
		}
	}

}

int32_t main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}




}
