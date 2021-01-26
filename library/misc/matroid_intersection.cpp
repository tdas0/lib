/**
 * Author: Tiago
 * Source: Tfg
 * Date: 2021-01-26
 * Intersecta duas matroides (para weighted só apagar a bfs/dfs e codar bellman-ford)
 * Se for IncrementalMatroid:
 * check(int x): checa se o x-ésimo elemento do ground set pode ser adicionado a basis
 * add(int x): adiciona o x-ésimo elemento do ground set a basis
 * clear(): limpa a basis (lembre de dar resize para o tamanho certo depois, é preferivel usar assign antes)
 * Se for RankMatroid:
 * Quando for dificil dar add, use RankMatroid (ex: cographic matroid), codar a função rank(vi x) 
 * que retorna o rank de um subconjunto x do ground-set
 * Time: O(enough) , memory : O(enough)
 * Status:tested, but no trustworthy probably
 */

struct IncrementalMatroid {
	virtual bool check(int x) = 0;
	virtual void add(int x) = 0;
	virtual void clear() = 0;
 
	template <class F, class ch>
	auto edge_finder(vi& ind_set, vector<ch>& iset, int v, F&& test, int c = 1) {
		return [&, v, test, c, done=0, ans=vi()]() mutable {
			if (v < sz(iset) && iset[v] != c) {
				this->clear();
				rep(cas, 0, 3) trav(u, cas ? ind_set : vi{v}) if (!cas || cas - 1 == test(u)) {
					if (!this->check(u)) return cas == 2 ? u : -1;
					this->add(u);
				}
				return sz(iset);
			}
			if (!done) {
				this->clear();
				trav(i, ind_set) if (i != v) this->add(i);
				rep(u, 0, sz(iset)) if (iset[u] != c && test(u) && this->check(u)) ans.push_back(u);
			}
			if (done < sz(ans)) return ans[done++];
			return -1;
		};
	};
};
        
struct RankMatroid {
	virtual int rank(const vi &ind_set) = 0;
 
	template <class F, class ch>
	auto edge_finder(vi& ind_set, vector<ch>& iset, int v, F&& test, int c = 1) {
		return [&, v, test, c, done=0]() mutable {
			if (v < sz(iset) && iset[v] != c) {
				vi cur[2];
				rep(cas, 0, 3) trav(u, cas ? ind_set : vi{v}) if (!cas || cas - 1 == test(u)) {
					cur[cas <= 1 ? 0 : 1].push_back(u);
				}
				auto go = [&](int mid) {
					auto got = cur[0];
					got.insert(got.end(), cur[1].begin(), cur[1].begin() + mid);
					return rank(got) == sz(got);
				};
				int l = 0, r = sz(cur[1]);
				if(go(r)) return sz(iset);
				if(!go(0)) return -1;
				while(l+1 != r) {
					int mid = (l + r) / 2;
					if(go(mid)) {
						l = mid;
					} else {
						r = mid;
					}
				}
				return cur[1][l];
			}
			vi cur, other;
			trav(i, ind_set) if (i != v) cur.push_back(i);
			rep(u, 0, sz(iset)) if (iset[u] != c && test(u)) other.push_back(u);
			auto go = [&](int l, int r) {
				auto got = cur;
				got.insert(got.end(), other.begin() + l, other.begin() + r);
				return rank(got) > sz(cur);
			};
			int l = 0, r = sz(other);
			if(!go(l, r)) return -1;
			while(l+1 != r) {
				int mid = (l + r) / 2;
				if(go(l, mid)) {
					r = mid;
				} else {
					l = mid;
				}
			}
			return other[l];
		};
	};
};
 


template <class M1, class M2>
vi solve_matroid_intersection(M1&& m1, M2&& m2, int n)
{
	vector<char> iset(n);
	vi ind_set;
	for(int i = n - 1; i >= 0; --i) if (m1.check(i) && m2.check(i))
		m1.add(i), m2.add(i), iset[i] = true, ind_set.push_back(i);
	while (1) {
		vi dist(n + 2, -1);
		auto edge_finder = [&](auto&& m, int v, int d) {
			return m.edge_finder(ind_set, iset, v, [&,d](int u){return dist[u] == d;});
		};
		queue<int> q({n + 1});
		dist[n + 1] = 0;
		while (dist[n] == -1 && !q.empty()) {
			int v = q.front(), u; q.pop();
			auto forward_edge = edge_finder(m1, v, -1);
			auto back_edge    = edge_finder(m2, v, -1);
			while (dist[n] == -1 && (u = dist[v]&1 ? back_edge() : forward_edge()) >= 0)
				q.push(u), dist[u] = dist[v] + 1; 
		}
		if (dist[n] == -1) break;
		auto dfs = [&](int v, int dv, auto&& dfs) -> bool{
			int u;
			auto forward_edge = edge_finder(m2, v, dv - 1);
			auto back_edge    = edge_finder(m1, v, dv - 1);
			while ((u = dv & 1 ? back_edge() : forward_edge()) >= 0){
					if (u == n) return true; 
					dist[u] = -1;
					if (dfs(u, dv - 1, dfs)) return iset[u] ^= 1, true;
				}
			return false;
		};
		while (dfs(n, dist[n], dfs)) {
			ind_set.clear();
			rep(i, 0, n) if (iset[i]) ind_set.push_back(i);
		}
	}
	return ind_set;
}


// examples of matroid
struct GaussMatroid : IncrementalMatroid{
	int n;
	vl ground , basis ;
	GaussMatroid(int n , vl ground ) : ground(ground) , n(n), basis(vl(62,0)){}
	bool check(int x){
		auto p = ground[x];
		for(int j = 61 ; j >= 0 ; j --){
			p = min(p , p^basis[j]);
		}
		return p > 0;
	}
	void add(int x){
		auto p = ground[x];
		for(int j = 61 ; j >= 0 ; j --){
			if((1LL<<j & p) && !basis[j]){
				basis[j] = p;
				break;
			} 
			p = min(p , p ^ basis[j]);
		}
	}
	void clear(){
		basis.assign(62,0);
	}
};

struct Binary_Matroid : RankMatroid {
	vector<vector<long long>> a;
	vector<long long> basis;
	vector<pair<int,int>> ground;
	Binary_Matroid(const vector<vector<long long>> &a, vector<pair<int,int>> ground) : a(a), ground(ground) {}
	bool check(int i) {
		auto p = ground[i];
		return accumulate(basis.begin(), basis.end(), a[p.first][p.second],
						  [&](long long x, long long y) { return min(x, x ^ y); });
	}
	void add(int i) {
		auto p = ground[i];
		long long x = a[p.first][p.second];
		if (x = accumulate(basis.begin(), basis.end(), x, [&](long long x, long long y) { return min(x, x ^ y); })) {
			for (int i = 0; i <= int(basis.size()); ++i) {
				if (i == int(basis.size()) || x > basis[i]) {
					basis.insert(basis.begin() + i, x);
					return;
				}
			}
		}
	}
	void clear() { basis.clear(); }
	int rank(const vi &ind_set) {
		clear();
		int ans = 0;
		for(auto i : ind_set) if(check(i)) {
			add(i);
			ans++;
		}
		return ans;
	}
};
 
// end