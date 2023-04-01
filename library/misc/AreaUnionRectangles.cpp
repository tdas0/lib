/*
  Area of The Union of Rectangles
  O(NlogN), using segment tree
  Status: Tested on Brazil Subreg and 2023 ICPC Asia Hong Kong
  Source: Naim
*/
struct Edge{
	int x,yMin,yMax;
	bool open;
	Edge(int x,int y1,int y2,bool type){
		this->x = x;
		yMin = y1,yMax = y2;
		open = type;
	}
	bool operator < (const Edge &e) const {
		return x<e.x;
	} 	
};

int n,m,h[MAXN*2]; //h has the comprimed x-coordinates
// for N rectangles there are 2*N x-points
int sum[MAXN*32],counter[MAXN*32]; // 32 for LARGE y

vector<Edge> edges;

void update(int no,int i,int j,int yMin,int yMax,bool open){
	
	if(h[j]<yMin || yMax<h[i])return;//out of bonds;
	
	int l = 2*no,r=2*no+1,m=(i+j)/2;
	

	if(yMin<=h[i] && h[j]<=yMax){
		counter[no]+= open ? 1 : -1;
		
		if(counter[no]){
			sum[no] = h[j] - h[i];
		}else sum[no] = sum[l] + sum[r];
		return;
	}

	if(i+1>=j)return;
	
	update(l,i,m,yMin,yMax,open);
	update(r,m,j,yMin,yMax,open);
	
	if(counter[no])sum[no] = h[j] - h[i];
	else sum[no] = sum[l]+sum[r]; 
	
	return;
}
int k;
int solve(){
	sort(h+1,h+1+k);
	
	int area = 0LL;
	
	sort(edges.begin(),edges.end());
	
	update(1,1,k,edges[0].yMin,edges[0].yMax,edges[0].open);

	for(int i=1;i<edges.size();i++){
		area+=sum[1]*1LL*(edges[i].x - edges[i-1].x);
		update(1,1,k,edges[i].yMin,edges[i].yMax,edges[i].open);
	}
	
	return area;
}

int32_t main(){
	fastio;
	
	map<int,int> mapa;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x1,x2,y1=0,y2;
		cin>>x1>>x2>>y2;
		Edge aux = Edge(x1,y1,y2,1);//abre
		Edge aux2 = Edge(x2,y1,y2,0);//fecha
		edges.pb(aux);
		edges.pb(aux2);
		mapa[y1];
		mapa[y2];
	}
	
	 k=0;
	for(map<int,int>::iterator it = mapa.begin();it!=mapa.end();it++){
		h[++k] = it->first;//erasing reductant heights and ordering them
	}
	cout<<solve()<<endl;
}
