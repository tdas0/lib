// begin of lazy seg
const int N = 500005;
ll st[4*N] , lazy[4*N];
void push(int l , int r , int curr){
	if(lazy[curr]){
		st[curr] += lazy[curr];
		if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
		lazy[curr] = 0 ;
	}
}
void pull(int l , int r , int curr){
	push(l,r,curr); int mid = l + (r-l)/2;
	if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
	st[curr] = min(st[2*curr] , st[2*curr+1]);
}
void upd(int x , int y, ll v,  int l, int r , int curr){
	int mid = (l+r)/ 2;  push(l,r,curr);
	if(l == x && r == y){
		lazy[curr] += v;
		push(l,r,curr);
		return ;
	}
	if(y <= mid) upd(x,y,v,l,mid,2*curr);
	else if(x > mid) upd(x,y,v,mid+1,r,2*curr+1);
	else upd(x,mid,v,l,mid,2*curr) , upd(mid+1,y,v,mid+1,r,2*curr+1);
	pull(l,r,curr);
}
ll qry(int x , int y , int l , int r , int curr){
	int mid = (l+r)/2; push(l,r,curr);
	if(l == x && r == y) return st[curr];
	if(y <= mid) return qry(x,y,l,mid,2*curr);
	else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
	return min(qry(x,mid,l,mid,2*curr) , qry(mid+1,y,mid+1,r,2*curr+1));
}
void build(int l , int r,  int curr){
	int mid = (l+r)/2;
	if(l == r){
		if(isl[l]) st[curr] = dist[l];
		else st[curr] = (ll) 1e18;
		return ;
	}
	build(l,mid,2*curr);
	build(mid+1,r,2*curr+1);
	st[curr] = min(st[2*curr] ,st[2*curr+1]);
}
// end of lazy seg
