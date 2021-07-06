/*
  IMPORTANTE: Para cada versão nova, fazer version[i] = new node();
  Sempre chamar BUILD na version[0]
*/
struct node{
  node *l,*r;
  int sum;
  node(int v = 0){
    l = r = NULL;
    sum = v;
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
    no->sum = old->sum + v;
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
	int esq = R->l->sum - L->l->sum;
	if(k <= esq) return get_kth(L->l, R->l, a, mid, k);
	return get_kth(L->r, R->r, mid + 1, b, k - esq);
}
