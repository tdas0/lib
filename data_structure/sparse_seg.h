/**
 * Author: Tiago
 * Source: own
 * Date: 2020-04-13
 * Description: Segtree esparsa com lazy
 * Com bump-allocator usa menos memoria e é muito mais rápida, só tem que cuidar pro tamanho do buf não ta pequeno/grande demais
 * Time: Both operations are $O(\log N)$.
 */



// alocator
static char buf[256000000];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}
// end

struct node{
	node* c[2];
	bool lazy = 0;
	int cnt = 0;
	node(){c[0] = c[1] = nullptr;}
	void push(int l , int r){
		if(!lazy) return ;
		if(l!=r){
			if(!c[0]) c[0] = new node();
			if(!c[1]) c[1] = new node();
			c[0]->lazy |= lazy , c[1]->lazy |= lazy;
		}
		cnt = r-l+1; lazy = 0;
		return ;
	}	
	void pull(int l, int r){
		push(l,r); int mid = l + (r-l)/2;
		cnt = 0;
		if(c[0]) c[0]->push(l, mid) , cnt += c[0]->cnt;
		if(c[1]) c[1]->push(mid+1, r), cnt += c[1]->cnt;
	}
	void upd(int x , int y , int v , int l , int r){
		int mid = l + (r-l)/2;
		if(x==l && y==r){
			lazy |= v; return ;
		}
		if(y <= mid){
			if(!c[0]) c[0] = new node();
			c[0]->upd(x,y,v,l,mid);
		}
		else if(x > mid){
			if(!c[1]) c[1] = new node();
			c[1]->upd(x,y,v,mid+1,r);
		}
		else{
			if(!c[0]) c[0] = new node();
			if(!c[1]) c[1] = new node();
			c[0]->upd(x,mid,v,l,mid) , c[1]->upd(mid+1,y,v,mid+1,r); 			
		}
		pull(l,r);
	}
	int qry(int x , int y , int l , int r){
		push(l,r);
		int mid = l + (r-l)/2;
		if(x == l && y == r){
			return cnt;
		}
		if(y <= mid){
			if(!c[0]) return 0;
			return c[0]->qry(x,y,l,mid);
		}
		else if(x > mid){
			if(!c[1]) return 0;
			return c[1]->qry(x,y,mid+1,r);
		}
		else{
			return (c[0] != nullptr ? c[0]->qry(x,mid,l,mid) : 0) + (c[1] != nullptr ? c[1]->qry(mid+1,y,mid+1,r) : 0);
		}
	}
};