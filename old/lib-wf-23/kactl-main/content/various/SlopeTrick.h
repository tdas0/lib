/*
 * Description: keep the value of a function while adding functions such as
 * g(x) = s|x-v|, g(x) = max(0,x-v)*s , g(x) = max(0,v-x)*s
 * Make f(x) <- f(x-a)
 * Make f(x) = min(f(Y) | Y <= x)
 * Make f(x) = min(f(Y) | Y >= x)
 * Source: https://github.com/ei1333/library/blob/master/structure/others/generalized-slope-trick.hpp
 * Complexity: $O(\logN)$ amortized
 */

struct SlopeTrick {
 private:
  using ll = long long;
  // x : coordenada, c : slope change
  struct P {
    ll x, c;
    P(ll _x, ll _c) : x(_x), c(_c) {}
    friend bool operator<(const P& a, const P& b) { return a.x < b.x; }
    friend bool operator>(const P& a, const P& b) { return a.x > b.x; }
  };
  ll addL, addR, min_y;
  priority_queue<P> L;
  priority_queue<P, vector<P>, greater<>> R;
  void pushL(ll x, ll c = 1) { L.emplace(x - addL, c); }
  void pushR(ll x, ll c = 1) { R.emplace(x - addR, c); }
  P getL() { return P{L.top().x + addL, L.top().c}; }
  P getR() { return P{R.top().x + addR, R.top().c}; }
  void popL() { L.pop(); }
  void popR() { R.pop(); }
 public:
  SlopeTrick() : addL(0), addR(0), min_y(0) {}
  // return {x, y} s.t. {argmin, min}
  pll get_min() {
    ll x = L.empty() ? R.empty() ? 0 : getR().x : getL().x;
    return {x, min_y};
  }
  void shift_L(ll a) { addL += a; }
  void shift_R(ll a) { addR += a; }
  // f(x) <- f(x - a)
  void shift_x(ll a) { addL += a, addR += a; }
  // f(x) <- f(x) + a
  void shift_y(ll a) { min_y += a; }
  // add (x-a)_+   _____/
  void add_xma(ll a, ll c = 1) {
    ll used = 0;
    while (used < c && !L.empty()) {
      auto [X, C] = getL();
      if (X <= a) break;
      popL();
      ll tmp = min(c - used, C);
      pushR(X, tmp);
      if (C != tmp) pushL(X, C - tmp);
      min_y += (X - a) * tmp;
      used += tmp;
    }
    if (used) pushL(a, used);
    if (c - used) pushR(a, c - used);
  }
  // add (a-x)_+   \_____
  void add_amx(ll a, ll c = 1) {
    ll used = 0;
    while (used < c && !R.empty()) {
      auto [X, C] = getR();
      if (X >= a) break;
      popR();
      ll tmp = min(c - used, C);
      pushL(X, tmp);
      if (C != tmp) pushR(X, C - tmp);
      min_y += (a - X) * tmp;
      used += tmp;
    }
    if (used) pushR(a, used);
    if (c - used) pushL(a, c - used);
  }
  // add |x-a|     \____/
  void add_abs_xma(ll a, ll c = 1) { add_xma(a, c), add_amx(a, c); }
  //  chmin right side \_/ -> \__
  void chmin_right() { decltype(R){}.swap(R); }
  //  chmin left side  \_/ -> __/
  void chmin_left() { decltype(L){}.swap(L); }
  // destructive merge
  void merge(SlopeTrick& r) {
    if (L.size() + R.size() < r.L.size() + r.R.size()) swap(*this, r);
    while (!r.L.empty()) {
      auto [x, c] = r.getL();
      r.popL();
      add_amx(x, c);
    }
    while (!r.R.empty()) {
      auto [x, c] = r.getR();
      r.popR();
      add_xma(x, c);
    }
    shift_y(r.min_y);
  }

  // eval f(x) O(|L| + |R|) TODO : verify
  ll eval(ll x) {
    ll y = min_y;
    auto LL{L};
    while (!LL.empty()) {
      auto [X, C] = LL.top();
      X += addL;
      if(X < x) break;
      y += (X - x) * C;
      LL.pop();
    }
    auto RR{R};
    while (!RR.empty()) {
      auto [X, C] = RR.top();
      X += addR;
      if(x < X) break;
      y += (x - X) * C;
      RR.pop();
    }
    return y;
  }
};
// solution to Sonya
int n,x;cin >> n; SlopeTrick trick;
rep(i,0,n){cin >> x; x-=i;trick.add_abs_xma(x,1);
    trick.chmin_right(); }
cout << trick.get_min().second << endl;