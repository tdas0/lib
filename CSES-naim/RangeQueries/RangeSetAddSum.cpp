/*
1) Increase each value in range [a,b] by x.
2) Set each value in range [a,b] to x.
3) Calculate the sum of values in range [a,b].
*/ 
#define int long long
typedef pair<int, int> pii;
const int MAXN = 200100;
int tree[4*MAXN];
pii lazy[4*MAXN];
 
void push(int no,int i,int j){
    int ad = lazy[no].ff;
    int se = lazy[no].ss;
    if(ad+se==0)return;
    lazy[no] = pii(0,0);
    if(se){
        tree[no] = 1LL*(j-i + 1)*(se);
        if(i!=j){
            lazy[2*no].ff = lazy[2*no+1].ff = 0;
            lazy[2*no].ss = lazy[2*no+1].ss = se;
        }
    }
    if(ad){
        tree[no]+=1LL*(j-i+1)*(ad);
        if(i!=j){
            if(lazy[2*no].ss)lazy[2*no].ss+=ad;
            else lazy[2*no].ff+=ad;
            if(lazy[2*no+1].ss)lazy[2*no+1].ss+=ad;
            else lazy[2*no+1].ff+=ad;
        }
    }
}
 
int query(int no,int i,int j,int a,int b){
    push(no,i,j);
    if(i>j || i>b || j<a)return 0;
    if(a<=i && j<=b)return tree[no];
    int l =2*no,r=2*no+1,m=(i+j)/2;
    return query(l,i,m,a,b)+query(r,m+1,j,a,b);
}
void update(int no,int i,int j,int a,int b,int op,int v){
    push(no,i,j);
    if(i>j || i>b || j<a)return;
    if(a<=i && j<=b){
        if(op==1){
            lazy[no] = pii(v,0);
        }else{
            lazy[no] = pii(0,v);
        }
        push(no,i,j);
        return;
    }    
    int l=2*no,r=2*no+1,m=(i+j)/2;
    update(l,i,m,a,b,op,v);
    update(r,m+1,j,a,b,op,v);
    tree[no] = tree[l] + tree[r];
}
 
 
int32_t main(){
    fastio;
    int n,q;
    cin>>n>>q;
    for(int i=0;i<4*MAXN;i++){
        lazy[i] = pii(0,0);
    } 
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        update(1,1,n,i,i,2,x);
    }
    while(q--){
        int op;
        cin>>op;
        if(op<=2){
            int a,b,x;
            cin>>a>>b>>x;
            update(1,1,n,a,b,op,x);
        }else{
            int a,b;
            cin>>a>>b;
            cout<<query(1,1,n,a,b)<<endl;
        }
    }
 
    // Math -> gcd it all
    //did you check N=1? Did you mix up N,M?
}