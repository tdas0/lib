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
#define pb push_back
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
char s[1000];

int To_int(string s){
    int res=0;
    for(int i=0;i<sz(s);i++){
        res = 10 * res + (s[i] - '0');
    }
    return res;
}

int main(){
    fastio;

    int n;
    while(true){
        cin >> n;
        if(n == 0)break;
       int bad=0;
       for(int aaa=0;aaa<n;aaa++){
         string s;
         cin>>s;
         vi v;
         for(int i = 2;i<sz(s);){
            string cur = "";
            while(i<sz(s) and s[i]!=':'){
                cur+=s[i];
                i++;
            }
            v.pb(To_int(cur));
            i++;
         }
         int ok = 1;
        
          int should;
          if(s[0]=='D'){
            if(make_tuple(v[0],v[1],v[2]) > make_tuple(9,30,0))ok=0;
            should = 8 * 3600;
          }else{
            if(make_tuple(v[0],v[1],v[2]) > make_tuple(12,30,0))ok=0;
            should = 9 * 3600;
          }
          
          if(make_tuple(v[0],v[1],v[2]) < make_tuple(8,30,0)){
            v[0] = 8,v[1] = 30,v[2] = 0;
          }  
          int t = 3600 * (v[3] - v[0]) + 60 * (v[4] - v[1]) + (v[5] - v[2]);
          

          //cout << v[0]<<" "<<v[1]<<" "<<v[2]<<endl;  

          if(t<should)ok=0;


          bad+=(ok == 0 ? 1 : 0);
       } 

       if(bad == 0){
        cout<<"All OK"<<endl;
       }else if(bad<=3){
        cout<<bad<<" Point(s) Deducted"<<endl;
       }else cout<<"Issue Show Cause Letter"<<endl;

    }
}
