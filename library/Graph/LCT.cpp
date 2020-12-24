// inutil mas sla kkkk
/**
 * Description: Link-Cut Tree. Given a function $f(1\ldots N)\to 1\ldots N,$ 
 	* evaluates $f^b(a)$ for any $a,b.$ \texttt{sz} is for path queries; 
 	* \texttt{sub}, \texttt{vsub} are for subtree queries. \texttt{x->access()} 
 	* brings \texttt{x} to the top and propagates it; its left subtree will be 
 	* the path from \texttt{x} to the root and its right subtree will be empty. 
 	* Then \texttt{sub} will be the number of nodes in the connected component
 	* of \texttt{x} and \texttt{vsub} will be the number of nodes under \texttt{x}.
 	* Use \texttt{makeRoot} for arbitrary path queries.
 * Time: O(\log N)
 * Usage: FOR(i,1,N+1)LCT[i]=new snode(i); link(LCT[1],LCT[2],1);
 * Source: Dhruv Rohatgi, Eric Zhang
	* https://sites.google.com/site/kc97ble/container/splay-tree/splaytree-cpp-3
	* https://codeforces.com/blog/entry/67637
 * Verification: (see README for links)
	* ekzhang Balanced Tokens
	* Dynamic Tree Test (Easy)
	* https://probgate.org/viewproblem.php?pid=578 (The Applicant)
 */
 typedef struct snode* sn;
struct snode { //////// VARIABLES
  sn p, c[2]; // parent, children
  sn extra; // extra cycle node for "The Applicant"
  bool flip = 0; // subtree flipped or not
  int val,sz; // value in node, # nodes in current splay tree
  int sub, vsub = 0; // vsub stores sum of virtual children
  ll sum = 0;
  snode(ll _val) : val(_val) {
    sum = _val;
    p = c[0] = c[1] = extra = NULL; calc(); }
  friend int getSz(sn x) { return x?x->sz:0; }
  friend int getSub(sn x) { return x?x->sub:0; }
  friend ll getSum(sn x){return x?x->sum:0;}
  void prop() { // lazy prop
    if (!flip) return;
    swap(c[0],c[1]); flip = 0;
    rep(i,0,2) if (c[i]) c[i]->flip ^= 1;
  }
  void calc() { // recalc vals
    rep(i,0,2) if (c[i]) c[i]->prop();
    sz = 1+getSz(c[0])+getSz(c[1]);
    sub = 1+getSub(c[0])+getSub(c[1])+vsub;
    sum = val + getSum(c[0])+getSum(c[1]);
  }
  //////// SPLAY TREE OPERATIONS
  int dir() {
    if (!p) return -2;
    rep(i,0,2) if (p->c[i] == this) return i;
    return -1; // p is path-parent pointer
  } // -> not in current splay tree
  // test if root of current splay tree
  bool isRoot() { return dir() < 0; } 
  friend void setLink(sn x, sn y, int d) {
    if (y) y->p = x;
    if (d >= 0) x->c[d] = y; }
  void rot() { // assume p and p->p propagated
    assert(!isRoot()); int x = dir(); sn pa = p;
    setLink(pa->p, this, pa->dir());
    setLink(pa, c[x^1], x); setLink(this, pa, x^1);
    pa->calc(); calc();
  }
  void splay() {
    while (!isRoot() && !p->isRoot()) {
      p->p->prop(), p->prop(), prop();
      dir() == p->dir() ? p->rot() : rot();
      rot();
    }
    if (!isRoot()) p->prop(), prop(), rot();
    prop();
  }
  sn fbo(int b) { // find by order
    prop(); int z = getSz(c[0]); // of splay tree
    if (b == z) { splay(); return this; }
    return b < z ? c[0]->fbo(b) : c[1] -> fbo(b-z-1);
  }
  //////// BASE OPERATIONS
  void access() { // bring this to top of tree, propagate
    for (sn v = this, pre = NULL; v; v = v->p) {
      v->splay(); // now switch virtual children
      if (pre) v->vsub -= pre->sub;
      if (v->c[1]) v->vsub += v->c[1]->sub;
      v->c[1] = pre; v->calc(); pre = v;
    }
    splay(); assert(!c[1]); // right subtree is empty
  }
  void makeRoot() { 
    access(); flip ^= 1; access(); assert(!c[0] && !c[1]); }
  //////// QUERIES
  friend sn lca(sn x, sn y) {
    if (x == y) return x;
    x->access(), y->access(); if (!x->p) return NULL;
    x->splay(); return x->p?:x; // y was below x in latter case
  } // access at y did not affect x -> not connected
  friend bool connected(sn x, sn y) { return lca(x,y); } 
  // # nodes above
  int distRoot() { access(); return getSz(c[0]); } 
  sn getRoot() { // get root of LCT component
    access(); sn a = this; 
    while (a->c[0]) a = a->c[0], a->prop();
    a->access(); return a;
  }
  sn getPar(int b) { // get b-th parent on path to root
    access(); b = getSz(c[0])-b; assert(b >= 0);
    return fbo(b);
  } // can also get min, max on path to root, etc
  //////// MODIFICATIONS
  void set(int v) { access(); val = v; calc(); } 
  friend void link(sn x, sn y, bool force = 0) { 
    assert(!connected(x,y)); 
    if (force) y->makeRoot(); // make x par of y
    else { y->access(); assert(!y->c[0]); }
    x->access(); setLink(y,x,0); y->calc();
  }
  friend void cut(sn y) { // cut y from its parent
    y->access(); assert(y->c[0]);
    y->c[0]->p = NULL; y->c[0] = NULL; y->calc(); }
  friend void cut(sn x, sn y) { // if x, y adj in tree
    x->makeRoot(); y->access(); 
    assert(y->c[0] == x && !x->c[0] && !x->c[1]); cut(y); }
};
const int MX = ;
sn LCT[MX];

// exemplo: soma dos valores entre u->v
LCT[u]->makeRoot();
LCT[v]->access();
cout << LCT[v]->sum << endl;
// criar um link (a filho de b):
link(LCT[a],LCT[b],1);
// tirar um link:
cut(LCT[u],LCT[v]);
// Achar o LCA:
sn Lca = lca(LCT[a],LCT[b]);
if(Lca==NULL)// n tao conectados
else cout << Lca->id << endl; // id dado na hora de inicializar 

// Exemplo2: Quando a ORDEM IMPORTA!!!
// ver a quantidade de parantesis para botar para que de A->B seja uma parantesisação boa:

// update val:
LCT[a]->access();
LCT[a]->val = v[a];
LCT[a]->calc();
// UPDATE ACESS/PROP:
friend int getPre(sn x,int b){
    return x?x->pre[b]:0;
  }
void prop() { // lazy prop
    if (!flip) return;
    swap(c[0],c[1]);
    swap(pre[0],pre[1]);
    flip = 0;
    rep(i,0,2) if (c[i]) c[i]->flip ^= 1;
  }
void calc() { // recalc vals
    rep(i,0,2) if (c[i]) c[i]->prop();
    sz = 1+getSz(c[0])+getSz(c[1]);
    sub = 1+getSub(c[0])+getSub(c[1])+vsub;
    tot = val + getTot(c[0])+getTot(c[1]);
    rep(i,0,2){
      pre[i] = min({0,getPre(c[i],i),getTot(c[i]) + val,getTot(c[i]) + val + getPre(c[i^1],i)});
    } // Tem que manter dois valores, se o caminho tiver normal ou invertido
}
// Answer query:
LCT[a]->makeRoot();
LCT[b]->access();

int tot = LCT[b]->tot,pre = LCT[b]->pre[0];
int res = abs(pre);
tot += res;
res += tot;
if(res!=0)cout << res<<endl;
else cout<<"balanced"<<endl;

// EXEMPLO 3 Vertex add/subtree query:
sub = val+getSub(c[0])+getSub(c[1])+vsub; // mudar isso em calc
//add:
LCT[p]->access();
LCT[p]->val+=x;
LCT[p]->calc();
// query (se p for a raiz soma na subarvore de v):
LCT[p]->makeRoot();
LCT[v]->access();
ll res = LCT[v]->vsub + LCT[v]->val;
