struct node{
  int na,nb;
  int ga,gb;
  node(){}
  node(int a,int b,int c,int d){
    na = a;
    nb = b;
    ga = c;
    gb = d;
  }
  node operator+(const node &o) const{
    node r;
    int puta = min(o.ga,nb);
    r.ga = o.ga - puta + ga;
    r.nb = nb - puta + o.nb;
    int putb = min(o.gb,na);
    r.gb = o.gb - putb + gb;
    r.na = na + o.na - putb;
    return r;
  }
};
// dizer qual lado eh mais pesado.
// Sei que A1<A2... mas nao sei o peso
for(int i=1;i<=n;i++){
    int x,s;
    cin >>x >> s;
    if(s == 1){ // coloca Ax kg na esq
        T.upd(x,node(1,0,1,0));
    }else T.upd(x,node(0,1,0,1)); // coloca Ax na dir

    node r = T.query(0,n+9);
    int oka = (r.nb == 0);
    int okb = (r.na == 0);
    if((!oka && !okb))cout << "?"<<endl;
    else if(oka)cout<<">"<<endl;
    else cout << "<" << endl;

}