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

ll tam = 1e5;
ll to_int(string s){
  ll res = 0;
  for(int i=0;i<s.size();i++){
    res = res* 10 + (s[i]-'0');
  }
  return res;
}

ll get(string s){
  string a="",b="";
  int pos = -1;

  for(int i=0;i<sz(s);i++){
    if(s[i] == '.'){
      pos = i;
      break;
    }
    a+=s[i];
  } 
  ll a1 = to_int(a);
  if(pos==-1){
    b="0";
  }else{
    for(int i=pos+1;i<sz(s);i++){
      b+=s[i];
    }
    if(b=="")b="0";
  }
  while(b.size()!=5)b+='0';
  ll a2 = to_int(b);
  ll res = tam * a1 + a2;
  //cout << res << endl;
  return res;
}

int main(){
  int t;
  cin>>t;
  while(t--){
    string s1,s2,s3;
    cin >> s1 >> s2 >> s3;
    ll d = get(s1),w = get(s2), l =get(s3);
    //cout << d<<" "<<l<<" "<<w<<endl;
    if(d*w*l > (d*w + w*l + l*d)*tam){
      cout<<"YES"<<endl;
    }else cout<<"NO"<<endl;
  }

}
