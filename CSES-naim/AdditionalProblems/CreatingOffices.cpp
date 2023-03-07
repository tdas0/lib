/*
A company wants to have offices in some cities, but the distance between any two
offices has to be at least d
What is the maximum number of offices they can have?
Sol: greedy
*/

#include <bits/stdc++.h>
#include <array>
#include <unordered_map>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vpi = vector<pair<int, int>>;
using pii = pair<ll, ll>;
 
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, d;
  cin >> n >> d;
  vector<vector<int>> adj(n);
  for(int i = 1; i < n; i++){
    int u, v; cin >> u >> v; u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  if(n == 2){
    if(d == 1) cout << "2\n1 2\n";
    else cout << "1\n1\n";
    return 0;
  }
  int z = 0;
  while(adj[z].size() == 1) z++;
  using T = priority_queue<pii, vector<pii>, greater<pii>>;
  vector<T> h(n);
  vector<int> dep(n);
  function<void(int,int)> dfs = [&](int u, int p){
    for(int v : adj[u]){
      if(v == p) continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      if(h[v].size() > h[u].size()) h[u].swap(h[v]);
      while(!h[v].empty()){
        auto x = h[v].top(); h[v].pop();
        h[u].push(x);
      }
      while(h[u].size() >= 2){
        auto x = h[u].top(); h[u].pop();
        auto y = h[u].top();
        if(x.first + y.first - 2 * dep[u] < d){
          
        } else {
          h[u].push(x);
          break;
        }
      }
    }
    if(h[u].empty() || h[u].top().first >= dep[u] + d){
      h[u].push({dep[u], u});
    }
  };
  dfs(z, -1);
  cout << h[z].size() << '\n';
  while(!h[z].empty()){
    auto [x, y] = h[z].top(); h[z].pop();
    cout << y+1 << ' ';
  }
  cout << '\n';
  return 0;
}