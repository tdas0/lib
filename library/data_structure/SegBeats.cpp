/*
 * SegBeats
 * Suporta as querys (note a ordenação):
 * 0: range CHMIN: ai = min(ai,x) , i em [l,r];
 * 1: range CHMAX: ai = max(ai,x) , i em [l,r];
 * 2: range ADD: ai = ai + x, i em [l,r]
 * 3: range SUM: soma ai, i em [l,r] / range MX / range MN
 * Dá pra mudar pra range XOR se tirar o ADD
 * Complexidade: O(logN) amorizado se não usar o ADD
 * Ou O(log^2) usando o ADD
 * Prova da complexidade (para as querys 0/1):
 * Toda vez que eu não paro, dois nós passam a ter o mesmo valor.
 * Para toda query é aumentado em O(1) a quantidade de valores distintos.
 * Então eu só não paro O((N + Q)*logN) vezes.
 * OBS: Declarar global para nao dar stack overflow ou mudar para um vector inves de array
 * Se quiser só "CHMAX", pode tirar o setmn e tirar a variável de max.
 * Status:
 * Tested on https://old.yosupo.jp/problem/range_chmin_chmax_add_range_sum
 * Referencias: 
 * https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeBeats.cpp
 * Benq, taken from yosupo judge
*/

typedef long long ll;
using T = pair<pair<ll,ll>,int>;
const ll INF = (ll)1e18; // nao usar LLONG_MAX
#define ff first
#define ss second
#define mid ((i+j)/2)
template<int SZ> struct Beats{
  
  struct node{
    int tam;
    ll sum,lazy;
    T mx,mn;
    T combMx(T a,T b){
      if(a < b)swap(a,b);
      if(a.ff.ff == b.ff.ff)
          return {{a.ff.ff,max(a.ff.ss,b.ff.ss)},a.ss + b.ss};
      return {{a.ff.ff,max(a.ff.ss,b.ff.ff)},a.ss};
    }
    T combMn(T a,T b){
      if(a > b)swap(a,b);
       if(a.ff.ff == b.ff.ff)
          return {{a.ff.ff,min(a.ff.ss,b.ff.ss)},a.ss + b.ss};
      return {{a.ff.ff,min(a.ff.ss,b.ff.ff)},a.ss};
    }
    node(){ // nulo
      mx = {{-INF,-INF},0},mn={{INF,INF},0};
      lazy=sum=0;
      tam=0;
    }
    node(ll x){
      lazy = 0;
      sum = x;
      mx = {{x,-INF},1};
      mn = {{x,+INF},1};
      tam = 1;
    }
    node (const node a,const node b){
        sum = a.sum + b.sum;
        lazy=0;
        tam = a.tam + b.tam;
        mx = combMx(a.mx,b.mx);
        mn = combMn(a.mn,b.mn);
    }
    void setmn(ll x){
      if(mx.ff.ff <= x)return;
      sum-=(mx.ff.ff - x)*mx.ss;
      if(mn.ff.ff == mx.ff.ff)mn.ff.ff = x;
      if(mn.ff.ss == mx.ff.ff)mn.ff.ss = x;
      mx.ff.ff=x;
    }
    void setmx(ll x){
      if(mn.ff.ff >= x)return;
      sum-=(mn.ff.ff - x)*mn.ss;
      if(mx.ff.ff == mn.ff.ff)mx.ff.ff = x;
      if(mx.ff.ss == mn.ff.ff)mx.ff.ss = x;
      mn.ff.ff=x;
    }
    void setsum(ll x){
      mx.ff.ff+=x,mx.ff.ss+=x;
      mn.ff.ff+=x,mn.ff.ss+=x;
      sum+=x*tam;
      lazy+=x;
    }
  }tree[4*SZ];
  
  void push(int no,int i,int j){
    if(i==j)return;
    for(int k=0;k<2;k++){
      if(tree[no].lazy)tree[no*2 + k].setsum(tree[no].lazy);
      tree[no*2+k].setmx(tree[no].mn.ff.ff);
      tree[no*2+k].setmn(tree[no].mx.ff.ff);
    }
    tree[no].lazy=0;
  }
  
  void upd(int no,int i,int j,int a,int b,ll x,int op){ // (1,1,n,L,R,x,tipo de query)
    push(no,i,j);
    if(i>b || j<a)return;
    if(op == 0){ // mn
      if(x>=tree[no].mx.ff.ff)return;
    }else if(op==1){//mx
      if(x<=tree[no].mn.ff.ff)return;
    }
    if(a<=i and j<=b){
      if(op==0){
        if(x > tree[no].mx.ff.ss){
          tree[no].setmn(x);
          return push(no,i,j);
        }
      }else if(op==1){
        if(x < tree[no].mn.ff.ss){
          tree[no].setmx(x);
          return push(no,i,j); 
        }
      }else{
        tree[no].setsum(x);
        return push(no,i,j);
      }
    }
    upd(2*no,i,mid,a,b,x,op),upd(2*no+1,mid+1,j,a,b,x,op);
    tree[no] = node(tree[2*no],tree[2*no+1]);
  }
  node query(int no,int i,int j,int a,int b){//(1,1,n,l,r)
    push(no,i,j);
    if(i>b || j<a)return node();
    if(a<=i and j<=b)return tree[no];
    return node(query(2*no,i,mid,a,b),query(2*no+1,mid+1,j,a,b));
  }

  node build(int no,int i,int j,vector<ll>& a){//vector 1 indexado/build(1,1,n,a)
    if(i==j){
      return tree[no] = node(a[i]);
    }
    return tree[no] = node(build(2*no,i,mid,a),build(2*no+1,mid+1,j,a));
  }// OBRIGATORIO CHAMAR UM BUILD!
};
