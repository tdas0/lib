#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i = a; i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9+7;

vector<int> solve(string s){
  vector<int> I (s.size());
  vector<int> cnt (26);
  for (int i = s.size()-1; i >= 0; i--) {
    for (int j = 0; j < s[i]-'a'; j++) {
      I[i] += cnt[j];
    }
    cnt[s[i]-'a']++;
  }
  return I;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s; cin >> s;
  ll n; cin >> n;
  vector<int> I = solve(s);
  reverse(begin(s), end(s));
  vector<int> II = solve(s);
  reverse(begin(s), end(s));
  reverse(begin(II), end(II));
  ll ans = 0;
  for (int i = 0; i < s.size(); i++) {
    ans += (I[i]%P + II[i]%P) % P;
    ans %= P;
  }
  ans *= n % P; ans %= P;
  ans *= ((n-1)%P + P) % P; ans %= P;
  ans *= (P+1)/2; ans %= P;
  for (int i = 0; i < s.size(); i++) {
    ans += (I[i]%P) * (n%P);
    ans %= P;
  }
  cout << ans << "\n";
}
