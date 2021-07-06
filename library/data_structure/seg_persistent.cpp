/*
  IMPORTANTE: Para cada versão nova, fazer version[i] = new node();
  Sempre chamar BUILD na version[0]
  
  Exemplos:
  kth menor range https://www.spoj.com/problems/MKTHNUM/
  distintos em range https://www.spoj.com/problems/DQUERY/
  soma k maiores: https://codeforces.com/group/Yeeas6y9bL/contest/335318 - problema E
*/
struct node{
  node *l,*r;
  int sum;
 int vl; ll tot; // PODE TIRAR SE NÃO FOR USAR SOMA DOS K MAIORES 
  node(int v = 0){
    l = r = NULL;
    sum = v;
   tot = v;//  PODE TIRAR SE NÃO FOR USAR SOMA DOS K MAIORES 
  }
};
typedef node* pnode;

pnode version[N];

void build(pnode no,int i,int j){
  if(i == j){
    return;
  }
  int mid = (i+j)>>1;
  no->l = new node();
  no->r = new node();
  build(no->l,i,mid);
  build(no->r,mid+1,j);
}

void upd(pnode no,pnode old,int i,int j,int p,int v){

  if(i == j){
    no->sum = old->sum + v; // PARA SOMA DOS K MAIORES, FAÇA no->sum = old->sum + 1
    no->vl = v; // PODE TIRAR SE NÃO FOR USAR SOMA DOS K MAIORES 
    no->tot = old->tot + v;//  PODE TIRAR SE NÃO FOR USAR SOMA DOS K MAIORES 
    return;
  }
  int mid = (i+j)>>1;
  if(p<=mid){
    no->r = old->r;
    if(no->l == NULL)no->l = new node();
    upd(no->l,old->l,i,mid,p,v);
  }else{

    no->l = old->l;
    if(no->r == NULL)no->r = new node();
    upd(no->r,old->r,mid+1,j,p,v);
  }
  assert(no->l!=NULL and no->r!=NULL);
  no->sum = no->l->sum + no->r->sum;
  no->tot = no->l->tot + no->r->tot; //  PODE TIRAR SE NÃO FOR USAR SOMA DOS K MAIORES 
}

int query(pnode no,int i,int j,int a,int b){
  if(i > j or i > b or j < a or no == NULL)return 0;
  if(a<=i and j<=b)return no->sum;
  int mid = (i+j)>>1;
  return query(no->l,i,mid,a,b) + query(no->r,mid+1,j,a,b);
}

// Se for usar essa função, deve chamar update +1 na posicao = valor
// !!!!
int get_kth(node *L, node *R, int a, int b, int k){
	if(a == b) return a;
	int mid = (a+b)>>1;
	int esq = R->l->sum - L->l->sum;
	if(k <= esq) return get_kth(L->l, R->l, a, mid, k);
	return get_kth(L->r, R->r, mid + 1, b, k - esq);
}


// Funções abaixos são para encontrar a soma dos K maiores elementos

int getsz(pnode p){
	if(!p)
		return 0;
	return p->sum;
}

ll gettam(pnode p){
	if(!p)
		return 0;
	return p->tot;
}

ll sum_k(pnode x , pnode y , int l , int r , int k){
	if(l == r){
		return ((ll)k) * x->vl;
	}
	if(k == (getsz(x) - getsz(y)))
		return gettam(x) - gettam(y);
	int mid = l + (r-l)/2;
	int tright = (x ? getsz(x->r) : 0) - (y ? getsz(y->r) : 0);
	int kleft = max(0 , k - tright);
	int kright = k - kleft;
	ll a = 0 , b = 0;
	if(kleft)
		a += sum_k(x->l , y?y->l:nullptr , l ,mid, kleft);
	if(kright)
		b += sum_k(x->r , y?y->r:nullptr , mid+1 ,r ,kright);
	return a + b;
}
