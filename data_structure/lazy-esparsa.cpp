/*
  * Author: Naim
  * Status: tested on https://codeforces.com/gym/100490/attachments problem E
  * Could be faster if take the functions out of the struct (why???)
*/
// overflow??
struct node{
 node*l,*r;
 int cnt;
 int lazy;
 node(){
   l = NULL;
   r = NULL;
   cnt=0;
   lazy=0;
 }
 
 void push(int i,int j){
  if(lazy==0)return;
  cnt+=lazy;
  if(i==j){
      lazy=0;
      return;
  }
  int mid = (i+j)>>1;
  if(l==NULL)l = new node();
  if(r==NULL)r = new node();

  l->lazy+=lazy;
  r->lazy+=lazy;
  lazy=0;
 }

 void update(int i,int j,int a,int b,int val){
  if(i>b || j<a)return;
  if(a<=i && j<=b){
      lazy+=val;
      push(i,j);
  }else{
    int mid = (i+j)>>1;
    if(!(i>b || mid<a)){
        if(l==NULL)l = new node();
        l->update(i,mid,a,b,val);
    }
    if(!(mid+1>b || j<a)){
        if(r==NULL)r = new node();
        r->update(mid+1,j,a,b,val);
    }


  }

 }

 int query(int i,int j,int a,int b){
    push(i,j);
    if(a<=i && j<=b)return cnt;
    else{
        int mid = (i+j)>>1;
        int op1=0,op2=0;
        if(!(i>b || mid<a)){
            if(l==NULL)op1=0;
            else op1 = l->query(i,mid,a,b);
        }
        if(!(mid+1>b || j<a)){
            if(r==NULL)op2=0;
            else op2 = r->query(mid+1,j,a,b);
        }

          return op1 + op2;
    }
 }

};

node* tree;
