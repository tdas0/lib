struct LAZY{
vector<ll> mn,lazy,mx;
int n;
LAZY(){}
LAZY(int _n){ // pass a vector/array if needed
  n = _n;
  mn.resize(4*n + 100,0);
  lazy.resize(4*n + 100,0);
  mx.resize(4 * n + 100,0);
}

void propagate(int no,int i,int j){
  if(lazy[no]==0)return;
  mn[no]+=lazy[no];
  mx[no]+=lazy[no];
  if(i!=j){
    lazy[2*no]+=lazy[no];
    lazy[2*no+1]+=lazy[no];
  }
  lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,ll v){
  propagate(no,i,j);
  if(i>b || j<a || i>j)return;
  if(a<=i && j<=b){
    lazy[no]+=v;
    propagate(no,i,j);
    return;
  }
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  update(l,i,m,a,b,v);
  update(r,m+1,j,a,b,v);  
  mn[no] = min(mn[l],mn[r]);
  mx[no] = max(mx[l],mx[r]);
}
void upd(int a,int b,ll v){
  update(1,1,n,a,b,v);
}

ll query(int no,int i,int j,int a,int b){
  if(i>b || j<a || i>j)return 1e15;
  
  propagate(no,i,j);
  
  if(a<=i && j<=b)return mn[no];
  
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  
  return min(query(l,i,m,a,b),query(r,m+1,j,a,b));
}
ll query(int a,int b){
  return query(1,1,n,a,b);
}

void pushdown(int no,int i,int j){
  propagate(no,i,j);
  int m = (i+j)/2,l=2*no,r=2*no+1;
  if(i!=j){
    propagate(l,i,m);
    propagate(r,m+1,j);
    mn[no] = min(mn[l],mn[r]);
    mx[no] = max(mx[l],mx[r]);
  }
 } 

  int bbL(int no,int i,int j,int L,int R,int val){
    pushdown(no,i,j);
    if(i > R or j<L)return N;// bad...
    if(mx[no] <= val)return N;
    if(i == j)return i;
    int m = (i+j)/2;
    int l=2*no,r=2*no + 1;

    if(i<L or j>R){
      return min(bbL(l,i,m,L,R,val),bbL(r,m+1,j,L,R,val));
    }
    if(mx[l] > val){
      return bbL(l,i,m,L,R,val);
    }
    return bbL(r,m+1,j,L,R,val);
  }
  int bbL(int L,int R,int val){
    return bbL(1,1,n,L,R,val);
  }
  int bbR(int no,int i,int j,int L,int R,int val){
    pushdown(no,i,j);
    if(i > R or j<L)return 0;// bad...
    if(mn[no] > val)return 0;
    if(i == j)return i;
    int m = (i+j)/2;
    int l=2*no,r=2*no + 1;

    if(i<L or j>R){
      return max(bbR(l,i,m,L,R,val),bbR(r,m+1,j,L,R,val));
    }

    if(mn[r] <= val){
      return bbR(r,m+1,j,L,R,val);
    }
    return bbR(l,i,m,L,R,val);
  }
  int bbR(int L,int R,int val){
    return bbR(1,1,n,L,R,val);
  }
};