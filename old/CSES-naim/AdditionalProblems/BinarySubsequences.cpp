// achar string com N subsequencias distintas
int solve(int x,int y){
  if(x<y)swap(x,y);
  if(x == 0 and y== 0)return 0;
  if(x==y)return 1e9;
  int qtd = x/(y+1);
  return solve(x%(y+1),y) + qtd;
}
string ans="";
void go(int x,int y,int a,int b){
  if(x==0 and y==0)return;
  if(x < y)return go(y,x,b,a);
  int qtd = x/(y+1);
  rep(i,0,qtd)ans+=char('0' + a);
  return go(x%(y+1),y,a,b);
}
int32_t main(){
  fastio;
  int n;
  cin >> n;
  int id=0;
  int res = 1e9;
  for(int x=0;x<=n;x++){
    int cur;
    if(res > (cur = solve(x,n-x))){
      res = cur;id = x;
    }
  }
  go(id,n-id,0,1);
  cout << ans << endl;
}