#include <bits/stdc++.h>
#define N 300010
#define sz(x) (int)(x).size()
using namespace std;
int n, m, vis[N],q;
vector<int> grafo[N], rev[N];
vector<pair<int, int> > ans;
void dfs1(int x){
    vis[x]=1;
    for(int i = 0; i < (int)grafo[x].size(); i++){
        int v= grafo[x][i];
        if(vis[v]) continue;
        ans.push_back({x, v});
        dfs1(v);
    }
}
void dfs2(int x){
    vis[x]=1;
    for(int i = 0; i < (int)rev[x].size(); i++){
        int v = rev[x][i];
        if(vis[v]) continue;
        ans.push_back({v, x});
        dfs2(v);
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>q;
    while(q--){
        cin>>n>>m;
        ans.clear();
        vector< pair<int, int> > edge;
       for(int i = 1; i <= n; i++){
        vis[i] = 0;
        grafo[i].clear();
        rev[i].clear();
       }
       for(int i = 1, a, b; i <= m; i++){
            cin>>a>>b;
            grafo[a].push_back(b);
            rev[b].push_back(a);
            edge.push_back({a, b});
       }
       dfs1(1);
       for(int i = 1; i <= n; i++) vis[i]=0;
       dfs2(1);
       sort(ans.begin(), ans.end());
       // for(auto x: ans) cout<<"edgfe "<<x.first<<" "<<x.second<<" || "<<m-2*n<<"\n";
       vector<pair<int, int> > resp;
       for(int i = 0; i < (int)edge.size(); i++){
        int a = edge[i].first, b = edge[i].second;
        if(!binary_search(ans.begin(), ans.end(), make_pair(a, b)))
            resp.push_back({a, b});
       }
       while((int)resp.size() > m-2*n) resp.pop_back();

       for(int i = 0; i < (int)resp.size(); i++){
        cout<<resp[i].first<<" "<<resp[i].second<<"\n";
       }
   }
}