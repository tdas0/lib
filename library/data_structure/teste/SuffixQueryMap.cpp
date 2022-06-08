// from benq
// build a map of (a1,b1),(a2,b2)...(ak,bk) satisfaing a1<a2<a3...<ak and b1>b2>b3...
// and find in a query the largest B such that a>=X
#define lb lower_bound

map<int,ll> m;
void ins(int a, ll b) {
    auto it = m.lb(a); if (it != end(m) && it->s >= b) return;
    it = m.insert(it,{a,b}); it->s = b;
    while (it != begin(m) && prev(it)->s <= b) m.erase(prev(it));
}
ll query(int x) { auto it = m.lb(x);
    return it == end(m) ? 0 : it->s; }
