/*
For each child, you know the amount of food they currently have
and the amount of food they want.
At each step, a child can give one unit of food to his or her neighbour.
What is the minimum number of steps needed?
*/
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<ll> a(n), b(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> b[i];
  for(int i = 0; i < n; i++) a[i] -= b[i];
  for(int i = 1; i < n; i++) a[i] += a[i - 1];
  sort(a.begin(), a.end());
  ll res = 0;
  for(int i = 0; i < n; i++) res += abs(a[i] - a[n / 2]);
  cout << res << '\n';
  return 0;