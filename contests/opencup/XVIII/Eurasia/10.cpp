#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef long long ll;
const double EPS = 1e-10;
typedef pair<ll,ll> pii;
int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 ifstream cin("input.txt");
 ofstream cout("output.txt");
 
  int t;
  cin>>t;
  while(t--){
	  ll n,L;
	  cin>>n>>L;
	  L = L*1000;
	  vector<pii> ac;
	  for(int i=0;i<n;i++){
		  ll a,t;
		  cin>>a>>t;
		  ac.pb(pii(a,t));
	  }
	  sort(ac.begin(),ac.end(),greater<pii>());
	  double t=0;
	  double cur=0;
	  double v=0;
	  for(int i=0;i<n;i++){
	  	 double tt = ((1.0*ac[i].ss)/1e6);
	  	 double a = ac[i].ff;
	  	 double tempo = (-1.0*v + 1.0*sqrt(1.0*v*v + 2.0*(L - cur)*a))/(1.0*a);
	  	
	    tt = min(tempo,tt);
     	t+=tt;
		cur+=(tt*tt*a)/2.0 + v*tt;
		v+=a*tt;
	 
		if(L-cur<EPS)break; 	 
 	 }
 
	 if(L-cur>EPS){
		 t+=(1.0*(L-cur))/v;
	 }
	  cout<<setprecision(10)<<fixed;
	  cout<<t<<endl;
  } 	 
 
}