#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
#define ff first
#define ss second
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<ll,ll> pll;

const int N = 400100;
const int M1 = 1e9 + 7;
const int M2 = 1e9 + 9;
const int P1 = 137, P2 = 139;

int n,k;
ll a[N], cnt[N];
ll p[N][2];

pll H = pll(0,0);



int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    pll pa = pll(0,0);
    p[0][0] = p[0][1] = 1;
    rep(i,1,N){
        p[i][0] = p[i-1][0] * P1 % M1;
        p[i][1] = p[i-1][1] * P2 % M2;
    }

    for(int i=2;i<=k;i++){
        pa.ff += p[i][0];
        pa.ss += p[i][1];
        pa.ff %= M1, pa.ss %= M2;
    }
    map<pll,int> mp;
    mp[H] = 0;
    int res=0;
    rep(i,1,n+1){
        cin >> a[i];
        if(a[i] == 1){
            H.ff += pa.ff;
            H.ss += pa.ss;
            H.ff %= M1, H.ss %= M2;
        }else{
            H.ff = (H.ff - p[a[i]][0] + M1) %M1;
            H.ss = (H.ss - p[a[i]][1] + M2) %M2;     
        }
        if(mp.count(H)){
            res = max(res,i - mp[H]);
        }
        else mp[H] = i;
    }
    cout << res << endl;
}
