int ans=0;
string s;
int vis[10][10];
void solve(int i,int j,int p){
	if(i==7 && j==1){
		
		if(p==48){
			ans++;
		}
		return;
	}
	if(p==48 || i==0 || i==8 || j==0 || j==8)return;
	int u = !vis[i-1][j];
	int d = !vis[i+1][j];
	int l = !vis[i][j-1];
	int r = !vis[i][j+1];
	
	if(u && d && !l && !r)return;
	if(!u && !d && l && r)return;
	
	vis[i][j] = 1;
	char c = s[p];
	int f = (c=='?' ? 1 : 0);
	if(d && (c=='D' || f)){
		solve(i+1,j,p+1);
	}
	if(u && (c=='U' || f)){
		solve(i-1,j,p+1);
	}
	if(l && (c=='L' || f)){
		solve(i,j-1,p+1);
	}
	if(r && (c=='R' || f)){
		solve(i,j+1,p+1);
	}
	
	vis[i][j] = 0;
	
}
 
int32_t main(){
	for(int i=0;i<8;i++)vis[i][0] = vis[0][i] = vis[8][i] = vis[i][8] = 1;
	fastio;
	cin>>s;
	solve(1,1,0);
	cout<<ans<<endl;
}