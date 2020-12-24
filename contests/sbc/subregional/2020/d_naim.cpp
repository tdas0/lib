// UPSOLVING - tested locally

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
#define int long long
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


struct kmp{
	vector<int> b, pos;
	vi s, p;
	//A = texto, B = padrao
	void build(vi A,vi B){
		s = A, p = B;
		int n = sz(s), m = sz(p);
		//p.pb(-1);
		b.resize(m + 1);
		b[0] = -1;
		for(int i = 0, j = -1; i < m; i++) {
			while(j >= 0 and p[i] != p[j]) j = b[j];
			j ++;
			b[i + 1] = j;
		}


		//achar posicoes onde o padrao aparece
		for(int i = 0, j = 0; i < n; i++){
			while(j >= 0 and s[i] != p[j]) j = b[j];
			j ++;
			if(j == m){
			  pos.push_back(i - j + 1);
			  j = b[j];
			}
		}
	}
	
} KMP;

const int N = 1e6 + 100;
const int M = 1e9 + 7;
int A[N];
int B[N];

template<class T>
struct Mat{
	int n, m; vector< vector<T> > d;
	Mat(int n , int m): n(n) , m(m){
		d.assign(n , vector<T>(m,0));
	}
	Mat() : Mat(0,0) {}

	Mat  operator*(const Mat&a){ // m == a.n
		Mat x(n,a.m);
		rep(i,0,n) rep(j,0,m) rep(k,0,a.m)
			(x.d[i][k] += (d[i][j] * (ll)a.d[j][k]))%=M;
		return x;
	}
	Mat operator+(const Mat&a){
		return Mat(*this)+= a;
	}
	Mat operator-(const Mat&a){
		return Mat(*this)-= a;
	}
	Mat & operator*=(const Mat&a){
		return *this = (*this)*a;
	}
	Mat & operator^=(const ll& x){
		return *this = pow(*this , x);
	}
	Mat operator^(const ll &x){
		return Mat(*this)^= x;
	}
	friend Mat pow(Mat a, ll p){
		Mat res(a.n,a.m); rep(i,0,a.n) res.d[i][i] = 1;
		for(; p ; p/=2 , a *= a) if(p&1) res *= a;
		return res;
	}
};

// dp(n,0) = (n-1)*dp(n-1,1)
// dp(n,1) = dp(n-1,0) + (n-2)*dp(n-1,1)

// dp(0,0) = 1,dp(0,1)=0



int32_t main(){
  fastio;
  int n;
  int m,k;
  cin >> n >> m >> k;
  vi d1,d2;
  for(int i=0;i<n;i++){
  	cin >> A[i];
  	if(i)d1.pb(mod(A[i] - A[i-1],m));
  }	  
  d1.pb(mod(A[0] - A[n-1],m));
  rep(i,0,n){
  	cin >> B[i];
  	if(i)d2.pb(mod(m - mod(B[i] - B[i-1],m),m));
  }
  d2.pb(mod(m - mod(B[0] - B[n-1],m),m));
  
  for(int i=0;i<sz(d2);i++){
  	d1.pb(d1[i]);
  }
  KMP.build(d1,d2);
  	
 
 Mat<ll> mat(2,2);
 mat.d[0][0]=0;
 mat.d[0][1] = n-1;
 mat.d[1][0] = 1;
 mat.d[1][1] = n-2;
 mat^=(k);
 ll res=0;
 ll inicial = mat.d[0][0] + 0 *mat.d[0][1];
 ll outro = mat.d[1][0] + 0 * mat.d[1][1];
 
 for(int pos : KMP.pos){
 	if(pos >= sz(d2))continue;
 	if(pos == 0){
 		res+=inicial;
 	}else{
 		res+=outro;
 	}
 	if(res>=M)
 		res-=M;
 }
  cout << res << endl;
  


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
