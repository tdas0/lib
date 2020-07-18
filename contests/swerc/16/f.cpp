#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

const int MAXN = 200100;
vector<int> g[MAXN];


struct coisa{
 int t,r,id;
};

int BIT[2*MAXN];
int tin[MAXN],tout[MAXN];
int t=0;

void dfs(int v,int p=-1){
    tin[v] = ++t;
    for(int i=0;i<g[v].size();i++){
        int to = g[v][i];
        if(to!=p){
            dfs(to,v);
        }
    }
    tout[v] = ++t;
}

int cmp(coisa a,coisa b){
    return a.t < b.t;
}
int sum(int x){
    int r=0;
    while(x>0){
        r+=BIT[x];
        x-=(x&-x);
    }
    return r;
}
void update(int x,int v){
    while(x<MAXN*2){
        BIT[x]+=v;
        x+=(x&-x);
    }
}
int res[MAXN];
int32_t main(){
    int n;
    cin>>n;
    vector<coisa> v(n);
    int root=0;
    for(int i=0;i<n;i++){
        int m;
        cin>>m>>v[i].t>>v[i].r;
        v[i].id = i+1;
        if(m==-1)root = i+1;
        if(m!=-1)g[m].pb(i+1);
    }
   
    dfs(root);
    sort(v.begin(),v.end(),cmp);
    
    for(int i=0;i<n;){
        int T = v[i].t;
        vector<coisa> aux;
        while(i<n && v[i].t==T){
            aux.pb(v[i]);
            int id = v[i].id;
            res[id] = sum(tout[id]) - sum(tin[id]);
            i++;
        }
        for(int j=0;j<aux.size();j++){
            update(tin[aux[j].id],aux[j].r);
            
        }

    }
    for(int i=1;i<=n;i++){
        cout<<res[i]<<endl;
    }

}