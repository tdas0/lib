// dado pares de valores (x,y)
// escolher A caras para serem X
// B para serem Y e maximizar soma
// ninguem pode ser X e Y ao mesmo tempo
// a + b <= n, n<=2e5 , x,y<=1e9
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
const int N = 2e5;
pair<ll, ll> xs[N];
ll p[N], s[N];
 
int main() {
  cin.tie(0), ios::sync_with_stdio(0);
  int a, b, n, x, y;
  cin >> a >> b >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    xs[i] = {x, y};
  }
  sort(xs, xs + n,
       [](auto i, auto j) { return i.first - i.second > j.first - j.second; });
  ll sum = 0;
  priority_queue<ll> q;
  for (int i = 0; i < n; i++) {
    sum += xs[i].first;
    q.push(-xs[i].first);
    if (q.size() > a) {
      sum += q.top();
      q.pop();
    }
    p[i] = sum;
  }
  sum = 0;
  q = priority_queue<ll>();
  for (int i = n - 1; i >= 0; i--) {
    sum += xs[i].second;
    q.push(-xs[i].second);
    if (q.size() > b) {
      sum += q.top();
      q.pop();
    }
    s[i] = sum;
  }
  ll mx = 0;
  for (int i = a - 1; i < n - b; i++) mx = max(mx, p[i] + s[i + 1]);
  cout << mx << '\n';
}