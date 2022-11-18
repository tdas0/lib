/**
  * Author: Bruno malleta
  * Status: Tested on https://codeforces.com/group/3qadGzUdR4/contest/101707
  *         Problem I
  * Description: Find the max_dot product in a set of points
  * May also work for other functions. Not tested for that
  */

int extreme(const function<bool(P, P)>& cmp,vector<P>& pol) {
  int n = sz(pol);
  auto extr = [&](int i, bool& cur_dir) {
    cur_dir = cmp(pol[(i+1)%n], pol[i]);
    return !cur_dir and !cmp(pol[(i+n-1)%n], pol[i]);
  };
  bool last_dir, cur_dir;
  if (extr(0, last_dir)) return 0;
  int l = 0, r = n;
  while (l+1 < r) {
    int m = (l+r)/2;
    if (extr(m, cur_dir)) return m;
    bool rel_dir = cmp(pol[m], pol[l]);
    if ((!last_dir and cur_dir) or
        (last_dir == cur_dir and rel_dir == cur_dir)) {
      l = m;
      last_dir = cur_dir;
    } else r = m;
  }
  return l;
}
ll max_dot(P v,vector<P>&pol) {
  return v.dot(pol[extreme([&](P p, P q) { return p.dot(v) > q.dot(v); },pol)]);
}
