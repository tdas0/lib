/*
	Complete SegTree that accept every Monoid
	Change Lazy to sum up lazys
	Change Node+Lazy to apply
	Change Node+Node to merge
	Change breakCondition and tagCondition to Beats
	call Build(1,n,1,v<node>) to build
	in constructor, pass identity element of monoid (node) and null element of lazy 
*/


struct Lazy{
	Lazy operator+(Lazy R){
		return {};
	}
};

struct Node{
	Node operator+(Lazy L){
		return {};
	}	
	Node operator+(Node R){
		return {};
	}
};

template<class U = Node, class L = Lazy>
class SegmentTree{
public:
	SegmentTree() = default;
	SegmentTree(int n, U identity , L zero){
		tagLazy.assign(4*n+2, 0);
		node.resize(4*n+2,identity), lazy.resize(4*n+2,zero);
		node[0] = identity;
		lazy[0] = zero;
	}	
	void pullUp(int id, int l, int r){
		if(l != r)
			node[id] = node[2*id] + node[2*id + 1];
	}
	void pushDown(int id, int l, int r){
		if(tagLazy[id]){
			node[id] = node[id] + lazy[id];
			if(l != r){
				lazy[2*id] = lazy[2*id] + lazy[id] , tagLazy[2*id] = 1;
				lazy[2*id + 1] = lazy[2*id + 1] + lazy[id] , tagLazy[2*id + 1] = 1; 
			}
			tagLazy[id] = 0 , lazy[id] = lazy[0];
		}
	}
	bool breakCondition(int ql, int qr, L v, int l, int r, int id){
		if(qr < l || r < ql){
			return 1;
		}
		else {
			return 0;
		}
	}
	bool tagCondition(int ql, int qr, L v, int l, int r, int id){
		if(ql <= l && r <= qr){
			return 1;
		}
		else{
			return 0;
		}
	}
	void build(int l, int r, int id, const vector<U> &a){
		int mid = l + (r-l)/2;
		if(l == r){
			node[id] = a[l];
			return ;
		}
		build(l, mid, 2*id,a);
		build(mid+1, r, 2*id+1,a);
		pullUp(id, l, r);
	}
	void upd(int ql, int qr, L v, int l, int r, int id){
		pushDown(id, l, r);
		if(breakCondition(ql, qr, v, l, r, id)){
			return ;
		}
		if(tagCondition(ql, qr, v, l, r, id)){
			tagLazy[id] = 1;
			lazy[id] = lazy[id] + v;
			pushDown(id, l, r);
			return ;
		}
		int mid = l + (r-l)/2;
		upd(ql, qr, v, l, mid, 2*id);
		upd(ql, qr, v, mid+1, r, 2*id+1);
		pullUp(id, l, r);
	}
	U query(int ql, int qr, int l, int r, int id){
		pushDown(id, l, r);
		if(qr < l || r < ql)
			return node[0];
		if(ql <= l && r <= qr){
			return node[id];	
		}
		int mid = l + (r-l)/2;
		return query(ql, qr, l, mid, 2*id) + query(ql, qr, mid+1, r, 2*id+1);
	}
private:
	vector<bool> tagLazy;
	vector<U> node;
	vector<L> lazy;
};



