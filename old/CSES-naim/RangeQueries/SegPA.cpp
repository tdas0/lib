struct Seg{
  int n;
  vector<ll> a1,an,tree;
  Seg(){}
  Seg(int N){
    n = N;
    tree = a1 = an = vector<ll>(4*n + 100,0);
  }

  void flush(int no,ll i,ll j){
    if(a1[no] + an[no] == 0)return;
    // CAREFULL WITH OVERFLOW
    tree[no]+=1ll*(a1[no] + an[no])*(j-i+1)/2;

     
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    if(i!=j){
      ll step = (an[no] - a1[no])/(j - i);
      ll m = (mid - i);
    
      a1[L]+=a1[no];
      an[L]+=a1[no] + step * m;

      a1[R]+=a1[no] + (step * (m+1));
      an[R]+=an[no];
    }
    a1[no] = an[no] = 0;
  }

  void upd(int no,int i,int j,int a,int b,pll v){
    // v.ff + (i-a) * v.ss;
    flush(no,i,j);
    if(i > b || j <a)return;
    if(a<=i and j<=b){
      a1[no]+=v.ff + (v.ss)*ll(i - a);
      an[no]+=v.ff + (v.ss)*ll(j - a);
      flush(no,i,j);
      return;
    }
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    upd(L,i,mid,a,b,v);
    upd(R,mid+1,j,a,b,v);
    tree[no] = tree[L] + tree[R];
  } 
  void upd(int L,int R,int a,int d){
    upd(1,1,n,L,R,pll(a,d));
  }
  ll query(int no,int i,int j,int a,int b){
    flush(no,i,j);
    if(i > b || j < a)return 0;
    if(a<=i and j<=b)return tree[no];
    int mid = (i+j)>>1,L=no<<1,R=no<<1|1;
    return query(L,i,mid,a,b) + query(R,mid+1,j,a,b);
  }
  ll query(int a,int b){
    return query(1,1,n,a,b);
  }
};

// Com BIT

template<class T>
struct BIT{
 int n;
 int MAX;
 vector<T> bit;
 BIT(){}
 BIT(int _n){
   n = _n;
   MAX = n +2;
   bit.resize(n+10,0);
 }
 
 T sum(int x){
   T r=0;
   while(x>0){
     r+=bit[x];
     x-=(x&-x);
   }
   return r;
 }
 
 
 void upd(int x,T val){
  if(x==0)return;
   while(x<MAX){
     bit[x]+=val;
     x+=(x&-x);
   }
 }
 void upd(int l,int r,T val){
  if(l>r)return;
  upd(l,val);
  upd(r+1,-val);
 }
 
};
const int N = 200100;
BIT<ll> B[3];
 
void add_range(int L,int R,ll val){
  if(!val)return;
  //cout<<"add range ["<<L<<","<<R<<"] == "<<val<<endl;
  B[1].upd(L,val);
  B[1].upd(R+1,-val);
  B[0].upd(L,-val*(L-1));
  B[0].upd(R+1,+val*R);
}
 
ll PA(int a1,int r,int n){
  if(n==0)return 0;
  ll an = a1 + r*(n-1);
  //db3(a1,an,n);
  return (a1+an)*n/2;
}
 
void update(int L,int R,int r,int a1=1){
  add_range(L,R,a1-r);
  if(!r)return;
  // Para a PA:
  B[2].upd(L,R,r);
  ll tot1 = PA(r,r,L-1);
  
  add_range(L,L,-tot1);
  // Soma -(L-1)*r em [L,R]:
  add_range(L,R,-(L-1)*r);
  ll tot = PA(a1,r,R-L+1) + (R-L+1)*(L-1)*r + tot1;
  //db(tot);
  add_range(R+1,R+1,tot);
}
 
ll query(int x){
  if(x==0)return 0;
  // answer for [1...x]:
  ll sum0 = B[0].sum(x);
  ll sum1 = B[1].sum(x)*x;
  ll sum2 = 1ll*B[2].sum(x)*x*(x+1)/2;
  
  return sum0 + sum1 + sum2;
}
 
 
int32_t main(){
  fastio;
  int n,q;
  cin>>n>>q;
  rep(i,0,3)B[i] =BIT<ll>(N);
  for(int i=1;i<=n;i++){
    int x;cin>>x;
    update(i,i,0,x);
  }
  while(q--){
    int op,l,r;
    cin>>op>>l>>r;
    if(op==1){
      update(l,r,1,1);
    }else{
      ll ans = query(r) - query(l-1);
      cout << ans << endl;
    }
  }
}

// EDU - queries em so um ponto
const int MAX = 2e5+10;
 
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n, *v;
 
	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		if (!lazy[p]) return;
		int m = (l+r)/2;
		seg[2*p] += lazy[p]*(m-l+1);
		seg[2*p+1] += lazy[p]*(r-(m+1)+1);
		lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		prop(p, l, r);
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}
	ll update(int a, int b, ll x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			seg[p] += (ll)x*(r-l+1);
			lazy[p] += x;
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = update(a, b, x, 2*p, l, m) +
			update(a, b, x, 2*p+1, m+1, r);
	}
};
 
int v[MAX];
 
int main() { _
	int n, m; cin >> n >> m;
	//for (int i = 0; i < n; i++) v[i] = 1;
	seg::build(n+1, v);
	while (m--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r, a, d; cin >> l >> r >> a >> d; l--, r--;
			seg::update(l, l, a);
			seg::update(r+1, r+1, -a);
			if (l != r) {
				int qt = r-l;
				seg::update(l+1, l+qt, d);
				seg::update(l+qt+1, l+qt+1, -d*(ll)qt);
			}
		} else {
			int i; cin >> i; i--;
			cout << seg::query(0, i) << endl;
		}
	}
	exit(0);
}