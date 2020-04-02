struct tree{
 int n;
 vector<vector<int> > adj;
 vector<int> h;
 vector<vector<int> > layer;
 vector<int> pai;
 void init(int _n,vector<vector<int> > L){
     n = _n;
     adj = L;
     h.resize(n);
     layer.resize(n,vector<int>());
 }
 
 int dfs(int v,int p=-1){
    
    layer[h[v]].pb(v);
     int mx = h[v];
     for(int i=0;i<(int)adj[v].size();i++){
         int to = adj[v][i];
         if(to==p)continue;
         h[to] = h[v] + 1;
         pai[to] = v;
         mx = max(mx,h[to]);
         mx = max(mx,dfs(to,v));
     }
     return mx;
 }
 
 int levalize(int root){
    layer.resize(n,vector<int>());
    pai.resize(n);
    h.resize(n);
    for(int i=0;i<n;i++){
         layer[i].clear();
         pai[i] = 0;
         h[i] = 0;
     }
    pai[root] = root;
     return dfs(root);
 }
 
 vector<int> d;
 
 vector<int> find_center(){
     vector<int> prev;
     int u=0;
     for(int it=0;it<2;it++){
         
         prev.resize(n);
         for(int i=0;i<n;i++)prev[i]=  -1;
         queue<int> q;
         q.push(prev[u]=u);
         
         while(!q.empty()){
             u = q.front();
             q.pop();
             for(int i=0;i<(int)adj[u].size();i++){
                 int to = adj[u][i];
                 if(prev[to]>=0)continue;
                    prev[to] = u;
                    q.push(to); 
             }
         }
     }
     vector<int> path;
     path.pb(u);
     while(u!=prev[u]){
         path.pb(u = prev[u]);
     }
     int m = path.size();
     vector<int> res;
     if(m%2==0){
         res.pb(path[m/2 - 1]);
         res.pb(path[m/2]);
     }else{
         res.pb(path[m/2]);
     } 
     return res;
 }
 
    
};
 
 
bool isomorphic(tree T,int t,tree S,int s){
    int levels = T.levalize(t);
    if(levels!=S.levalize(s))return false;
    
    vector<vector<int> > longCodeS,longCodeT;
    longCodeS.resize(S.n+1,vector<int>());
    longCodeT.resize(T.n+1,vector<int>());
    
    vector<int>CodeS(S.n+1),CodeT(T.n+1);
    
    for(int x = levels;x>=0;x--){
        
        map<vector<int>,int> mp;
        
        for(int i=0;i<(int)S.layer[x].size();i++){
            int cur = S.layer[x][i];
            sort(td(longCodeS[cur]));
            mp[longCodeS[cur]];
        }
        for(int i=0;i<(int)T.layer[x].size();i++){
            int cur = T.layer[x][i];
            sort(td(longCodeT[cur]));
            mp[longCodeT[cur]];
        }
        int k=0;
        for(map<vector<int>,int>::iterator it = mp.begin();it!=mp.end();it++){
            it->second = ++k;
        }
        for(int i=0;i<(int)S.layer[x].size();i++){
            int cur = S.layer[x][i];
            CodeS[cur] = mp[longCodeS[cur]];
            longCodeS[S.pai[cur]].pb(CodeS[cur]);
        }
        for(int i=0;i<(int)T.layer[x].size();i++){
            int cur = T.layer[x][i];
            CodeT[cur] = mp[longCodeT[cur]];
            
            longCodeT[T.pai[cur]].pb(CodeT[cur]);
        }
        
        
        
    }
    
    
    
    return CodeS[s]==CodeT[t];
}
 
 
bool isomorphicNoRoot(tree T,tree S){
    vector<int> x = T.find_center();
    vector<int> y = S.find_center();
    if(x.size()!=y.size())return false;
    if(isomorphic(T,x[0],S,y[0]))return true;
    if(x.size()>1 && isomorphic(T,x[1],S,y[0]))return true;
    return false;
}
 
vector<vector<int> > adj;
vector<vector<int> > adj2;
void solve(){
    int n;
    cin>>n;
    adj.resize(n,vector<int>());
    adj2.resize(n,vector<int>());
    for(int i=0;i<n;i++){
        adj[i].clear();
        adj2[i].clear();
    }
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        adj2[a].pb(b);
        adj2[b].pb(a);
    }
    tree T;
    T.init(n,adj);
    tree S;
    S.init(n,adj2);
    
    
    
    if(isomorphicNoRoot(T,S)){
        cout<<"YES"<<endl;
    }else cout<<"NO"<<endl;
}
