/**
 * Author: Tiago Domingos
 * Date: 2020-04-28
 * Description: lazy seg
 * Time: O(nlog) 
 * Usage: decompose(root) cria a HLD com os preferred-path  da raiz root
 * change pull push and build for change the tree 
 * push é propagate
 * pull é atualizar o nó atual com base nos filhos
 * Status:tested 
 */
template <class T> 
struct lazy_seg{
public:
	vector<T>  st , lazy;
	lazy_seg(int n){
		st.resize(4*n + 1 , 0) , lazy.resize(4*n + 1, 0);
	}
	lazy_seg() = default;
	void push(int l , int r , int curr){
		if(lazy[curr] != 0){
			st[curr] += lazy[curr]*(r-l+1);
			if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
			lazy[curr] = 0 ;
		}
	}
	void pull(int l , int r , int curr){
		push(l,r,curr); int mid = l + (r-l)/2;
		if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
		st[curr] = (st[2*curr] + st[2*curr+1]);
	}
	void upd(int x , int y, T v,  int l, int r , int curr){
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
	T qry(int x , int y , int l , int r , int curr){
		int mid = (l+r)/2; push(l,r,curr);
		if(l == x && r == y) return st[curr];
		if(y <= mid) return qry(x,y,l,mid,2*curr);
		else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
		return (qry(x,mid,l,mid,2*curr) + qry(mid+1,y,mid+1,r,2*curr+1));
	}
	void build(int l , int r,  int curr){
		int mid = (l+r)/2;
		if(l == r){
			st[curr] = 0; 
			return ;
		}
		build(l,mid,2*curr);
		build(mid+1,r,2*curr+1);
		st[curr] = (st[2*curr]  + st[2*curr+1]);
	}
};