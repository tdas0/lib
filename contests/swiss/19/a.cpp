#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
#define N 300050
int n, v[N];
    vector<int> ans, pos;
void get(int X){
    if(X<=0) return;
    vector<int> aux;
    aux.pb(X);
    for(int j = 1; j <= 6; j++) aux.pb(v[j]);
    sort(all(aux));
    set<int> ss;
    for(int i = 1; i < 7; i++){
        ss.insert(aux[i]-aux[i-1]);
    }
    if(sz(ss) == 1){
        ans.pb(X);
    } 
}
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    for(int i = 1; i <= 6; i++) cin>>v[i];
    for(int i = 1; i <= 6; i++){
        for(int j = 1; j <= 6; j++)
            if(i!=j) pos.pb(v[i]-v[j]);
    }
    for(auto d: pos){
        for(int i = 1; i <= 6; i++){
            get(v[i]-d);
            get(v[i]+d);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    for(auto w: ans) cout<<w<<"\n";
    // cout<<"\n";
}
