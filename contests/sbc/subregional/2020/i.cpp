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

const int N = 100100,M = 1e9 + 7;
int dp[N][2];
vi g[N];
int flag[N];
void solve(int v){
	// dp[v][1] -> ja sei quem eu sou, preciso gastar em adj-1
	// e um deles pego por free
	// dp[v][0] -> nao sei quem sou, nao posso gastar economizar onde não dá
	int tot=0;
	int some = 0;
	int AAA=0;
	int cost[2] = {0,0};
	for(int to : g[v]){
		solve(to);
		AAA = 1;
		int op1 = dp[to][0];
		int op2 = dp[to][1] + 1;
		cost[1] = min(cost[1] + min(op1,op2),cost[0] + op2-1);
		cost[0] = cost[0] + min(op2,op1);
		if(op2-1 < op1){
			flag[v] = 1;
		}
	}
	if(!AAA){
		dp[v][0] = N;
		dp[v][1] = 0;
		return ;
	}
	dp[v][1] = min(cost[0],cost[1]);
	dp[v][0] = cost[0];
}


ll DP[N][2];

ll go(int v,int f){
	ll &x = DP[v][f];
	if(x!=-1)return x;
	x=0;
	for(int to : g[v]){
		go(to,0);
		go(to,1);
	}
	if(f==0){
		// todo mundo tem que ser min(op1,op2), se op1 == op2 bota os dois:
	  x = 1;
	  for(int to : g[v]){
		 int op1 = dp[to][0];
		 int op2 = dp[to][1] + 1;
		 ll ways = 0;
		 if(op1<=op2){
			ways+= go(to,0);
		 }
		 if(op2<=op1){
			 ways+=go(to,1);
		 }
		 x = (x * ways%M)%M;
	  }
	}else{

		int tam = sz(g[v]);

		ll pre[tam+10][2],suf[tam+10][2];
		for(int i=0;i<tam+10;i++){
			for(int j=0;j<2;j++){
				pre[i][j]=0;
			}
		}

		pre[0][0] = suf[tam+1][0] = 1;

		for(int i=1;i<=tam;i++){
			int to = g[v][i-1];

			int op1 = dp[to][0];
			int op2 = dp[to][1] + 1;
			ll ways=0;
			
			// NAO ECONOMIZAR
				if(op1<=op2){
					ways+=go(to,0);
				}
				if(op2<=op1){
					ways+=go(to,1);
				}
				ways%=M;
		   		pre[i][0] = pre[i-1][0]*ways%M;
		   		pre[i][1] = pre[i-1][1]*ways%M;
		    
		    // ECONOMIZAR:
		   	if(op2-1<op1 || (op2-1==op1 and !flag[v])){
		   		pre[i][1] = (pre[i][1] + pre[i-1][0] * go(to,1)%M)%M;
		   	}

		}

		for(int i=tam;i>=1;i--){
			int to = g[v][i-1];

			int op1 = dp[to][0];
			int op2 = dp[to][1] + 1;
			ll ways=0;
			
			// NAO ECONOMIZAR
				if(op1<=op2){
					ways+=go(to,0);
				}
				if(op2<=op1){
					ways+=go(to,1);
				}
				ways%=M;
		   		suf[i][0] = suf[i+1][0]*ways%M;
		   		suf[i][1] = suf[i+1][1]*ways%M;
		    
		    // ECONOMIZAR:
		   	if(op2-1<op1 || (op2-1==op1 and !flag[v])){
		   		suf[i][1] = (suf[i][1] + suf[i+1][0] * go(to,1)%M)%M;
		   	}
		 
		}

		if(!flag[v]){
			// Nao importa onde economiza, pode nao economizar:
			x = pre[tam][0];
			for(int i=1;i<=tam;i++){
			   int to = g[v][i-1];
			   int op1 = dp[to][0];
			   int op2 = dp[to][1] + 1;

			   if(op2-1<op1 || (op2-1==op2 and !flag[v])){
			   	 // posso economizar aqui:
			   	 ll ways = pre[i-1][0] * suf[i+1][0]%M * go(to,1)%M;
			   	 x = (x + ways)%M;
			   }

			}
		}else{
			// ONDE ECONOMIZA (???)

			 for(int i=1;i<=tam;i++){
			   int to = g[v][i-1];
			   int op1 = dp[to][0];
			   int op2 = dp[to][1] + 1;

			   if(op2-1<op1 || (op2-1==op2 and !flag[v])){
			   	 // posso economizar aqui:
			   	 ll ways = pre[i-1][0] * suf[i+1][0]%M * go(to,1)%M;
			   	 x = (x + ways)%M;
			   }

				  
			}
			
		}
		



	}

	return x;
}


int32_t main(){
  fastio;
  ms(DP,-1);
  int n;
  cin>>n;
  for(int i=2;i<=n;i++){
  	int p;
  	cin >> p;
  	g[p].pb(i);
  }
  solve(1);
  
  ll res=0;
  int v = 1;
  if(dp[v][1] + 1 <= dp[v][0]){
  	res+=go(v,1);
  }
  if(dp[v][0] <= 1 + dp[v][1]){
  	res+=go(v,0);
  }
  
  res%=M;
  if(res<0)res+=M;

  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
