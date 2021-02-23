/* A SEGTREE 1D NAO É A MESMA QUE A DA LIB
* NESSA SEG EU ADICIONO NO NÓ INVES DE MUDAR O VALOR DE ANTES
* Nao funciona para achar o maximo se eu puder trocar (i,j) por um valor menor depois
* Status: Tested on CSES para a operação de soma
* Complexidade: O(log^2) / O(N^2) de memoria  - ~0.48 sec na questao do cses para N = 1000 e q = 2e5 
*/
struct node{
  ll x;
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = x+rhs.x;
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(){}
  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, T val){ // pos 0index // SOMAR e NAO MUDAR
    pos+=n;
    for(st[pos] = st[pos] + val ; pos /= 2;)
          st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};


template <class T>
struct ST2D{
  vector<ST<T>> st; 
  int n,m; 
  T ini; 
  ST2D() = default;
  ST2D(int n ,int m, T ini):m(m),n(n),ini(ini),st(2*n,ST<T>(m,ini)){
  }
  void upd(int pos,int y, T val){ // pos 0index
    assert(pos<n and y<m);
    for(st[pos += n].upd(y,val) ; pos /= 2;){
      st[pos].upd(y,val);
    }
  }
  T query(int x , int y,int l,int r){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x].query(l,r) , x++;
      if(y&1) --y , rb = st[y].query(l,r) + rb;
    }
    return ra + rb;
  }
};
