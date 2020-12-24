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

int G[2],P[2];

void redo(){
	if((P[0]>=5 and P[0] - P[1] >= 2) || P[0]==10){
		P[0] = P[1] = 0;
		G[0]++;
	}
	if((P[1]>=5 and P[1] - P[0]>=2) || P[1]==10){
		P[0] = P[1] = 0;
		G[1]++;
	}

}

int turn = 0;
void print(){
	if(G[0]==2 || G[1]==2){
		cout << G[0];
		if(G[0]==2){
			cout<<" (winner) - ";
		}else cout<<" - ";
		cout << G[1];
		if(G[1]==2){
			cout<<" (winner)";
		}
		cout << endl;
	}else{
		cout << G[0]<<" ";
		cout << "("<<P[0];
		if(turn == 0){
			cout<<"*) - ";
		}else{
			cout<<") - ";
		}

		cout << G[1] <<" ";
		cout << "("<<P[1];
		if(turn==1){
			cout<<"*)\n";
		}else cout<<")\n";

	}
}

int32_t main(){
  fastio;
  string s;
  cin>>s;
  for(int i=0;i<sz(s);i++){
  	if(s[i]=='S'){
  		P[turn]++;
  	}else if(s[i]=='R'){
  		turn^=1;
  		P[turn]++;
  	}else{
  		print();
  	}
  	redo();
  }
  
   
  	
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
