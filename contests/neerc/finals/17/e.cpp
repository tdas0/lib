#include <bits/stdc++.h>
#define N 1050
#define sz(x) (int)(x).size()
using namespace std;
int n, v[N], qtd[N];
int ans[N];
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>v[i];
    for(int i = 1; i <= n; i++){
        if(v[i] > 0)qtd[v[i]] ++;
        else if(v[i] < 0){
            if(qtd[-v[i]] > 0) qtd[-v[i]] --;
            else{
                int yes=0;
                for(int j = 1; j <= i; j++){
                    if(v[j] == 0 and ans[j]==0){
                        ans[j] = -v[i];
                        yes=1;
                        break;
                    }
                }
                if(!yes){
                    cout<<"No\n";
                    return 0;
                }
            }
        }
    }
    vector<int> w;
    for(int i = 1; i <= n; i++){
        if(v[i] ==0) w.push_back(max(1, ans[i]));
    }
    cout<<"Yes\n";
    for(int i = 0; i < sz(w); i++) cout<<w[i]<<" \n"[i== sz(w) -1];
}