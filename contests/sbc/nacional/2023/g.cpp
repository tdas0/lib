#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 100100;
int x[N], y[N], d[N];
int n;
set<pii> S;

void solve(int Y,int xl,int xr,int rot){
    int tam = xr - xl + 1;
    vector<int> sum(tam + 100);

    auto Somar = [&](int l,int r){
        sum[l - xl]++;
        sum[r+1 - xl]--;
    };

    auto interHor = [&](int yy,int Xl,int Xr){
        if(yy != Y)return ;
        Xl = max(Xl,xl);
        Xr = min(Xr,xr);
        if(Xl<=Xr){
            Somar(Xl,Xr);
        }
    };
    auto interVert = [&](int x,int yl,int yr){
        if(yl > yr)return;
        if(yl <= Y && Y <= yr){
            if(xl <= x && x<= xr){
                Somar(x,x);
            }
        }
    };
    

    for(int i=2;i<=n;i++){
        int xx = x[i], yy = y[i];
        int dd = d[i];
        if(rot)swap(xx,yy); // check?
        if(dd == 0){
            if(Y == yy){
                if(xl <= xx && xx<=xr){
                    Somar(xx,xx);
                }
            }
            continue;
        }

        interHor(yy-dd,xx-dd,xx+dd);
        interHor(yy+dd,xx-dd,xx+dd);
        // nao repetir borda
        interVert(xx-dd,yy-dd + 1,yy+dd - 1);
        interVert(xx+dd,yy-dd + 1,yy+dd - 1);
    }
    rep(i,1,tam+1){
        sum[i] += sum[i-1];
    }
    rep(x,xl,xr+1){
        if(sum[x - xl] == n-1){
            // todos aqui
            if(rot){
                S.insert({Y,x});
            }else{
                S.insert({x, Y});
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);    
    cin >> n;
    rep(i,1,n+1){
        cin >> x[i] >> y[i] >> d[i];
        int xx = x[i] + y[i],  yy = x[i] - y[i];
        x[i] = xx, y[i] = yy;
    }
    int xx = x[1], yy = y[1];
    int dd = d[1];
    solve(yy + dd, xx-dd, xx + dd,0);
    solve(yy - dd, xx-dd, xx + dd,0);
    solve(xx+dd,yy-dd,yy+dd,1);
    solve(xx-dd,yy-dd,yy+dd,1);

    set<pii> Ss;
    for(auto [x,y] : S){
        // x = X + Y
        // y = X - Y
        // (x+y)/2 = X
        // (x-y)/2 = Y
        if((x+y)&1)continue;
        if((x-y)&1)continue;
        int X = (x+y)/2, Y = (x - y)/2;
        Ss.insert({X,Y});
    }
    for(auto [x,y] : Ss)cout << x<<" "<<y<<endl;
}
