// menor ciclo
// n<=2500,m<=5000
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 25e2 + 7;
 
int n;
int m;
int d[N];
vector<int> g[N];
int main()
{
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    queue<int> q;
    int ans = INT_MAX;
    for(int i = 1; i <= n; i ++){
        memset(d, 0x3f, sizeof d);
        d[i] = 0;
        q.push(i);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto to: g[v]){
                if(d[to] > 1e9){
                    d[to] = d[v] + 1;
                    q.push(to);
                }else if(d[to] >= d[v]){
                    ans = min(ans, d[v] + 1 + d[to]);
                }
            }
        }
    }
    if(ans > 1e9) ans = -1;
    cout << ans << "\n";
}
 