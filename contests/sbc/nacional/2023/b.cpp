#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;




int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi a(3*n);
    rep(i,0,3*n)cin >> a[i];
    sort(all(a));
    int ok = 1;
    for(int i=0;i<3*n;i+=3){
        int ok2=1;
        rep(j,i,i+3)if(a[j] != a[i])ok2=0;
        ok&=ok2;
    }
    cout << (!ok ? "Y" : "N") << endl;
}
