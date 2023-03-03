// solves problem F from Brazil subreg 2022
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

#define sq(x) ((x)*(ll)(x))

struct pt { // ponto
	int x, y;
	pt(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const int c) const { return pt(x*c, y*c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

struct line { // reta
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

// comparador pro set pra fazer sweep line com segmentos
bool operator <(const line& a, const line& b) {
	// assume que os segmentos tem p < q
	if (a.p == b.p) return ccw(a.p, a.q, b.q);
	if (a.p.x != a.q.x and (b.p.x == b.q.x or a.p.x < b.p.x))
		return ccw(a.p, a.q, b.p);
	return ccw(a.p, b.q, b.p);
}

int main() { _
	int n; cin >> n;
	vector<int> baixo;
	// ponto, se eh rem, r, id, se eh bico, id do pol
	vector<tuple<pt, int, line, int, int, int>> w;
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		vector<pt> v(k);
		int mi = INF;
		for (pt& p : v) {
			cin >> p;
			mi = min(mi, p.x);
		}
		for (int j = 0; j < k; j++) {
			pt A = v[j], B = v[(j+1)%k];
			line r(A, B);
			if (r.q < r.p) swap(r.p, r.q);
			if (r.p.x == r.q.x) continue;
			w.emplace_back(r.p, 0, r, baixo.size(), (B.x == mi), i+1);
			w.emplace_back(r.q, 1, r, baixo.size(), 0, i+1);
			baixo.push_back(A.x < B.x);
		}
	}
	sort(w.begin(), w.end());
	set<tuple<line, int, int>> se;
	vector<int> p(n+1, -1);
	vector<vector<int>> g(n+1);
	for (auto [__, rem, r, id, bico, pol] : w) {
		if (bico) {
			auto it = se.lower_bound({r, 0, 0});
			if (it == se.end()) p[pol] = 0; // ninguem em cima
			else {
				auto [___, id_cima, pol_cima] = *it;
				if (baixo[id_cima]) p[pol] = p[pol_cima];
				else p[pol] = pol_cima;
			}
			g[p[pol]].push_back(pol); 
		}
		if (!rem) se.emplace(r, id, pol);
		else se.erase({r, id, pol});
	}
  // coisa da questao de achar "diametro"
	int ans = 0;
	function<int(int,int)> dfs = [&](int i, int d) {
		int ma1 = d, ma2 = 0;
		for (int j : g[i]) {
			int d2 = dfs(j, d+1);
			if (d2 > ma1) swap(d2, ma1);
			if (d2 > ma2) swap(d2, ma2);
		}
		ans = max(ans, 2*ma1 + ma2 - 2*d);
		return ma1;
	};
	dfs(0, 0);
	cout << ans << endl;
	exit(0);
}
