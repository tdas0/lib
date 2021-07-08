#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define dbg_loc() cerr << __PRETTY_FUNCTION__ << " : " << __LINE__ << "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p){ 
	return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container,typename T=typename enable_if<!is_same<T_container,string>::value, typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v){ 
	os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; 
}
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ 
	cerr << ' ' << H; 
	dbg_out(T...); 
}
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
#ifdef LOCAL 
#define dbg(...) cerr<<"(" << #__VA_ARGS__<<"):" , dbg_out(__VA_ARGS__) , cerr << endl
#else
#define dbg(...)
#endif

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}

template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Lazy{
	Mint a , b;
	Lazy operator+(Lazy R){
		return {R.a , R.b};
	}
};


struct Node2{
	Mint a , b;
	Node2 operator+(Lazy L){
		return {L.a , L.b};
	}	
	Node2 operator+(Node2 R){
		return { a*R.a, b + a * R.b};
	}	
};
struct Node{
	Mint a , b;
	Node operator+(Lazy L){
		return {L.a , L.b};
	}	
	Node operator+(Node R){
		return { a*R.a, R.b + R.a * b};
	}	
	Node operator+(Node2 R){
		return { a*R.a, R.b + R.a * b};
	}
};

template<class U = Node, class L = Lazy>
class SegmentTree{
public:
	SegmentTree() = default;
	SegmentTree(int n, U identity , L zero){
		tagLazy.assign(4*n+2, 0);
		node.resize(4*n+2), lazy.resize(4*n+2);
		node[0] = identity;
		lazy[0] = zero;
	}	
	void pullUp(int id, int l, int r){
		if(l != r)
			node[id] = node[2*id] + node[2*id + 1];
	}
	void pushDown(int id, int l, int r){
		if(tagLazy[id]){
			node[id] = node[id] + lazy[id];
			if(l != r){
				lazy[2*id] = lazy[2*id] + lazy[id] , tagLazy[2*id] = 1;
				lazy[2*id + 1] = lazy[2*id + 1] + lazy[id] , tagLazy[2*id + 1] = 1; 
			}
			tagLazy[id] = 0 , lazy[id] = lazy[0];
		}
	}
	bool breakCondition(int ql, int qr, L v, int l, int r, int id){
		if(qr < l || r < ql){
			return 1;
		}
		else {
			return 0;
		}
	}
	bool tagCondition(int ql, int qr, L v, int l, int r, int id){
		if(ql <= l && r <= qr){
			return 1;
		}
		else{
			return 0;
		}
	}
	void build(int l, int r, int id, const vector<U> &a){
		int mid = l + (r-l)/2;
		if(l == r){
			node[id] = a[l];
			return ;
		}
		build(l, mid, 2*id,a);
		build(mid+1, r, 2*id+1,a);
		pullUp(id, l, r);
	}
	void upd(int ql, int qr, L v, int l, int r, int id){
		pushDown(id, l, r);
		if(breakCondition(ql, qr, v, l, r, id)){
			return ;
		}
		if(tagCondition(ql, qr, v, l, r, id)){
			tagLazy[id] = 1;
			lazy[id] = lazy[id] + v;
			pushDown(id, l, r);
			return ;
		}
		int mid = l + (r-l)/2;
		upd(ql, qr, v, l, mid, 2*id);
		upd(ql, qr, v, mid+1, r, 2*id+1);
		pullUp(id, l, r);
	}
	U query(int ql, int qr, int l, int r, int id){
		pushDown(id, l, r);
		if(qr < l || r < ql)
			return node[0];
		if(ql <= l && r <= qr){
			return node[id];	
		}
		int mid = l + (r-l)/2;
		return query(ql, qr, l, mid, 2*id) + query(ql, qr, mid+1, r, 2*id+1);
	}
private:
	vector<bool> tagLazy;
	vector<U> node;
	vector<L> lazy;
};

// begin of HLD

// #include "../data_structure/SegLazy.cpp"
template<class U = Node , class L = Lazy>
class HLD{
public:
	HLD(int n , U identity , L zero): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
		seg = SegmentTree<U,L>(n , identity , zero);
		seg2 = SegmentTree<Node2,L>(n,{identity.a,identity.b},zero);
		vector<U> v(n , identity);
		vector<Node2> v2(n , {1,0});
		seg.build(0,n-1,1,v);
		seg2.build(0,n-1,1,v2);
		this->identity = identity;
		this->zero = zero;
	}
	void add_edge(int x , int y){
		g[x].push_back(y);
		g[y].push_back(x);
		edges ++ ;
		assert(edges < n);
	}
	void dfs_sz(int x , int par = -1){
		Sz[x] = 1;
		trav(w, g[x]){
			if(w == par) continue;
			dfs_sz(w,x);
			Sz[x] += Sz[w];
			if(Sz[w] > Sz[g[x][0]] || g[x][0] == par) swap(w, g[x][0]);
		}
	}
	void dfs_dec(int x , int par = -1){ 
		in[x] = tin++;
		allin(w, g[x]){
			if(w == par) continue;
			p[w] = x;
			Hd[w] = ((w == g[x][0]) ? Hd[x] : w);
			dfs_dec(w,x); 
		}
		out[x] = tin;
	}
	void decompose(int root){
		Hd[root] = root;
		dfs_sz(root);
		dfs_dec(root);
	}
	int lca(int x , int y){
		while(Hd[x] != Hd[y]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			y = p[Hd[y]];
		}
		return in[x] < in[y] ? x : y ;
	}
	void update_subtree(int x , L v){
		seg.upd(in[x] , out[x]-1 , v, 0 , n-1 , 1);
		return ;
	}
	void update_path(int x , int y , L v , bool c = 0){
		int u = lca(x,y);
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			seg.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
			seg2.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) seg.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1) , seg2.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1);
		return ;
	}
	U query_path(int x , int y , bool c = 0){  // se a ordem nao importar
		int u = lca(x,y);
		U ans = identity;
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			ans =  ans + seg.query(in[Hd[y]] , in[y] , 0, n-1, 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]){ 
			ans = ans + seg.query(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1);
		}
		return ans;
	}
	vector< vpi >  segments(int x , int y , bool c = 0){ // segmentos que tenho que perguntar na segtree
		int u = lca(x,y);
		U ans = identity;
		bool cur = 1;
		vector<pair< int,int >  > paths[2];
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y) , cur ^= 1;
			pii range = {in[Hd[y]] , in[y]};
			paths[cur].push_back(cur ? range : pii(range.S,range.F));
		}
		if(in[x] > in[y]) swap(x,y) , cur ^= 1;
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]){ 
			pii range = {in[u] + 1 - (c ? 1 : 0) , in[y]};
			paths[cur].push_back(cur ? range : pii(range.S,range.F));
		}
		reverse(all(paths[1]));
		return {paths[0] , paths[1]};		
	}
	U process(vector< vpi> ranges){
		U ansL = identity , ansR = identity;
		for(auto w : ranges[0]){
			ansL = (w.F < w.S) ?  (ansL +seg.query(w.F,w.S,0,n-1,1)):(ansL + seg2.query(w.S,w.F,0,n-1,1));
		}
		for(auto w : ranges[1]){
			ansR = (w.F < w.S) ?  (ansR +seg.query(w.F,w.S,0,n-1,1)):(ansR + seg2.query(w.S,w.F,0,n-1,1));			
		}
		return ansL + ansR;
	}
	U query_subtree(int x){
		return seg.query(in[x] , out[x]-1 , 0, n-1, 1);
	}

private:
	U identity;
	L zero;
	SegmentTree<U,L> seg;
	SegmentTree<Node2 , L> seg2;
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};

// end of HLD


void solve(){
	int n , q;
	scanf("%d%d" , &n , &q);
	HLD<> HLD(n , {1,0} , {0,0});
	vector<Node> a(n);
	for(int i = 0 ; i <n; i ++){
		int u , v;
		scanf("%d%d" , &u , &v);
		a[i] = {u,v};
	}
	for(int i = 0 ; i < n-1; i ++){
		int u , v;
		scanf("%d%d" , &u , &v);
		HLD.add_edge(u,v);
	}
	HLD.decompose(0);
	for(int i = 0 ; i <n;  i++){
		HLD.update_path(i,i,{a[i].a , a[i].b},1);
	}
	for(int i = 0 ; i < q; i ++){
		int a , b , c, d;
		scanf("%d%d%d%d" , &a , &b , &c , &d);
		if(a == 0){
			HLD.update_path(b,b,{c,d},1);
		}
		else{
			auto p = HLD.segments(b,c,1);
			auto ans = HLD.process(p);
			printf("%d\n" , (int) (ans.a * Mint(d) + ans.b));
		}
	}
}
 
 
int32_t main(){
	solve();
}
 
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?) , n , m ?
	* do smth instead of nothing and stay organized
	* WRITE/DRAW STUFF DOWN
	* DONT OVERCOMPLICATE 
*/
