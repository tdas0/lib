 // UPSOLVING - locally tested (quaseeeee)
 #include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) ((int)v.size())
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b, ll e ,ll m) {
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return mod(ans,m);
}


struct hash_interval
{
	ll c, mod;
	vector<ll> h, p;
	hash_interval(){}
	hash_interval(const string &s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1)
	{
		p[0] = 1;
		h[0] = 0;
		for (int i = 0; i < sz(s); i++)
		{
			h[i + 1] = (c * h[i] + s[i]) % mod;
			p[i + 1] = (c * p[i]) % mod;
		}
	}

	// Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
	ll get(int a, int b)
	{
		return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
	}
};

const int N = 100100;
string A[N],B[N];
hash_interval H1[N],H2[N];
hash_interval h1[N],h2[N];

bool bad1[N],bad2[N];


pll get1(int n,int l,int r){
	return pll(H1[n].get(l,r),h1[n].get(l,r));
}
pll get2(int n,int l,int r){
	return pll(H2[n].get(l,r),h2[n].get(l,r));
}
const int M = 1e9 + 7;
const int MOD2 = 998244353;
int32_t main(){
  fastio;
  int n,m;
  cin >> n >> m;
  map<pll,int> all1,all2;
  assert(n<N and m<N);
  for(int i=0;i<n;i++){
  	cin >> A[i];
  	H1[i] = hash_interval(A[i],3145739,M);
  	h1[i] = hash_interval(A[i],805306457,MOD2);
  	all1[get1(i,0,sz(A[i])-1)] = i+1;
  }
  for(int i=0;i<m;i++){
  	cin >> B[i];
  	H2[i] = hash_interval(B[i],3145739,M);
  	h2[i] = hash_interval(B[i],805306457,MOD2);

  	all2[get2(i,0,sz(B[i])-1)] = i+1;
  }

  map<pll,int> r1,r2;
  for(int i=0;i<n;i++){
  	int tam = sz(A[i]);
  	for(int k=1;k<tam;k++){
  		if(all1.count(get1(i,0,k-1))){
  			r1[get1(i,k,tam - 1)]=1;
  		}
  	}
  }
  for(int i=0;i<m;i++){
  	int tam = sz(B[i]);
  	for(int k=tam-1;k>=1;k--){
  		if(all2.count(get2(i,k,tam-1))){
  			r2[get2(i,0,k-1)] = 1;
  		}
  	}
  }


  int res1=0,res2=0;


  set<int> S;
  for(int i=0;i<n;i++){
  	int tam = sz(A[i]);
  	int ok=0;
    vi badK;
  	for(int k=1;k<tam;k++){
  		if(all1.count(get1(i,0,k-1)) and r2.count(get1(i,k,tam - 1))){
  			bad1[i] = 1;
  			badK.pb(k);
        ok=1;
  		}
  	}
  	if(!ok)continue;
  	for(int k : badK){
  		if(all1.count(get1(i,0,k-1))){
        int id = all1[get1(i,0,k-1)] - 1;
        bad1[id] = 1;
        S.insert(id);
  		}
  	}

  }
  
  for(int i=0;i<m;i++){
  	int tam = sz(B[i]);
  	int ok =0;
    vi badK;
  	for(int k=tam-1;k>=1;k--){
  		if(all2.count(get2(i,k,tam-1)) and r1.count(get2(i,0,k - 1))){
  			ok=1;
  			bad2[i] = 1;
        badK.pb(k);
  		}
  	}
  	if(!ok)continue;

  	for(int k : badK){
  		if(all2.count(get2(i,k,tam-1))){
  			bad2[all2[get2(i,k,tam-1)] - 1] = 1;
  		}
  	}

   }

   for(int i=0;i<n;i++){
   	 if(bad1[i])res1++;
   }
   rep(i,0,m){
   	 if(bad2[i])res2++;
   }


  cout << n-res1<<" "<<m-res2 << endl;

  
  


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
