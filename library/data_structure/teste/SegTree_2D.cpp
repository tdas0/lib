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
  void upd(int pos, T val){ // pos 0index - ADICIONA VAL / NAO MUDA O VALOR PRA VAL
    pos+=n;
    st[pos] = st[pos] + val; 
    //cout << "here "<<pos<<" "<<st[pos].x<<endl;
    for(; pos /= 2;)
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

template<class T>
struct ST_2D{
  vector<ST<T> > st;
  int n,m; 
  T ini;
  ST_2D(){}
  ST_2D(int nn, int mm,T iini){
    n=nn;
    m=mm;
    ini = iini;
    st = vector<ST<T> >(2*n , ST<T>(m,ini));
  }
  void upd(int i,int pos,node val){ // pos 0index
      for(st[i+=n].upd(pos,val);i/=2;){
        st[i].upd(pos,val);
      }
  }
  T query(int Li,int Lj,int Ri,int Rj){ // [x,y] , x, y -0index
    //assert(Li<n and Ri<n and Lj<m and Rj<m);
    T res = ini;
    int x = Li,y = Ri;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) res = res + st[x].query(Lj,Rj) , x++;
      if(y&1) --y , res = st[y].query(Lj,Rj) + res;
    }
    return res;
  }
};
