template <typename T>
vector<T> faulhaber(const T& up, int n) {
  vector<T> ex(n + 1);
  T e = 1;
  for (int i = 0; i <= n; i++) {
    ex[i] = e;
    e /= i + 1;
  }
  vector<T> den = ex;
  den.erase(den.begin());
  for (auto& d : den) {
    d = -d;
  }
  vector<T> num(n);
  T p = 1;
  for (int i = 0; i < n; i++) {
    p *= up + 1;
    num[i] = ex[i + 1] * (1 - p);
  }
  vector<T> res = num * inverse(den);
  res.resize(n);
  T f = 1;
  for (int i = 0; i < n; i++) {
    res[i] *= f;
    f *= i + 1;
  }
  return res;
}
 /// ????????????????????//
