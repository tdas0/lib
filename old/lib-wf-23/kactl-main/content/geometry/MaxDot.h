/**
 * Author: gustavoM32/caderno-zika
 * Description: ponto extremo em relacao a cmp(p, q) = p mais extremo q
 * ConvexHull must be sorted as usual
 * Status: Tested
 */
int extreme(const function<bool(P, P)>& cmp,vector<P> pol) {
    int n = pol.size();
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
int max_dot(P v) {
    return extreme([&](P p, P q) { return p*v > q*v; });
}
pair<int, int> tangents(P p) {
    auto L = [&](P q, P r) { return ccw(p, r, q); };
    auto R = [&](P q, P r) { return ccw(p, q, r); };
    return {extreme(L), extreme(R)};
}