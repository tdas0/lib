#include <bits/stdc++.h>
#define pb push_back
#define int long long
#define double long double
using namespace std;

const int N = 50;
double fat[N];
int dp[N][N][N];

    int d,H;
int solve(int h,int id,int last){
    if(h<0)return 0;
    if(id==d+1){
        if(h==0)return 1;
        return 0;
    }
    int &x = dp[h][id][last];
    if(x!=-1)return x;
    x=0;
    for(int i=last;i<=h;i++){
        x+=solve(h-i,id+1,i);
    }
    return x;
}


set<vector<int> > S;

void build(int h,int id,int last,vector<int> v){
    if(h<0)return;
    if(id==d+1){
        if(h==0)S.insert(v);
        return;
    }
    for(int i=last;i<=h;i++){
        if(solve(h-i,id+1,i)){
            vector<int> v2 = v;
            v2.pb(i);
            build(h-i,id+1,i,v2);
        }
    }
    return;
}

int32_t main(){
    memset(dp,-1,sizeof(dp));
    cin>>d>>H;
    H--;
    fat[0] = 1;
    for(int i=1;i<N;i++){
        fat[i] = (i*fat[i-1]);
    }
    vector<int> v2;
    build(H,1,0,v2);
    set<int> res;
    for(set<vector<int> >::iterator it = S.begin();it!=S.end();it++){
        vector<int> v = *it;
        double tot = fat[H];
        for(int i=0;i<v.size();i++){
            tot = (tot/fat[v[i]]);
        }
        res.insert((int)tot);
    }
    for(set<int>::iterator it =res.begin();it!=res.end();it++){
        cout<<*it<<endl;
    }


}