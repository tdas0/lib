/*
TODO: adicionar descrição
status: testada em https://dmoj.ca/problem/noi05p2/ (0.6 TL e 64mb)
*/


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define pt node*

struct node{
	int v,sum,prf,suf,sz,bst,lz,prior; 
	bool lazy , flip;
	pt c[2];
	node(int v){
		c[0] = c[1] = nullptr;
		this->v = sum = prf = suf = bst = v , lz = 0 , sz = 1 , prior = rng();
		lazy = flip = 0;
	}
	~node(){
		delete c[0];
		delete c[1];
	}
};

pt t = nullptr;


int getsz(pt t){
	if(!t)
		return 0;
	return t->sz;
}

void prop(pt &t){
	if(!t)
		return;
	if(t->flip){
		t->flip = false;
		swap(t->c[0] , t->c[1]);
		if(t->c[0])
			swap(t->c[0]->suf, t->c[0]->prf);
		if(t->c[1])
			swap(t->c[1]->suf, t->c[1]->prf);
		rep(i,0,2) if(t->c[i]){
			t->c[i]->flip ^= 1;
		}
	}
	if(t->lazy){
		if(t->lz < 0){
			t->v = t->suf = t->prf = t->bst = t->lz;
		}
		else{
			t->v = t->lz;
			t->suf = t->prf = t->bst = t->lz * getsz(t);
		}
		t->sum = getsz(t) * t->lz ; 
		rep(i,0,2) if(t->c[i]){
			t->c[i]->lazy = 1 , t->c[i]->lz = t->lz;
		}
		t->lz = 0 , t->lazy = 0;
	}
}

pt upd(pt t){
	if(!t)
		return t;
	prop(t);
	t->sz = 1;
	t->sum = t->suf = t->prf = t->bst = t->v;
	if(t->c[0]){
		prop(t->c[0]);
		t->bst = max({t->bst , t->c[0]->bst , t->c[0]->suf + t->prf});
		t->prf = max(t->c[0]->sum + t->prf, t->c[0]->prf);
		t->suf = max(t->c[0]->suf + t->sum, t->suf);
		t->sum = t->c[0]->sum + t->sum;
		t->sz += t->c[0]->sz;
	}	
	if(t->c[1]){
		prop(t->c[1]);
		t->bst = max({t->bst, t->c[1]->bst, t->suf + t->c[1]->prf});
		t->prf = max(t->sum + t->c[1]->prf, t->prf);
		t->suf = max(t->suf + t->c[1]->sum, t->c[1]->suf);
		t->sum = t->sum + t->c[1]->sum;
		t->sz += t->c[1]->sz;
	}
	return t;
}


pair<pt,pt> split(pt t , int k){
	if(!t)
		return {t,t};
	prop(t);
	if(getsz(t->c[0]) >= k){
		auto p = split(t->c[0] , k);
		t->c[0] = p.S;
		return {p.F, upd(t)};
	}
	else{
		auto p = split(t->c[1] , k - getsz(t->c[0]) - 1);
		t->c[1] = p.F;
		return {upd(t), p.S};
	}
}

pt merge(pt l, pt r){
	if(!l || !r)
		return l?:r;
	prop(l) , prop(r);
	if(l->prior > r->prior){
		l->c[1] = merge(l->c[1], r);
		return upd(l);
	}
	else{
		r->c[0] = merge(l, r->c[0]);
		return upd(r);
	}	
}


void del(int pos, int tot){
	auto p = split(t, pos-1);
	auto z = split(p.S, tot);
	t = merge(p.F, z.S);
	delete z.F;
}

void traversal(pt t);

void modify(int pos, int tot, int c){
	auto p = split(t, pos-1);
	auto z = split(p.S , tot);
	if(z.F)
		z.F->lazy = 1 , z.F->lz = c;
	p.S = merge(upd(z.F) , z.S);
	t = merge(p.F , p.S);
}

void reverse(int pos , int tot){
	auto p = split(t, pos-1);
	auto z = split(p.S , tot);
	if(z.F)
		z.F->flip ^= 1;
	p.S = merge(upd(z.F) , z.S);
	t = merge(p.F, p.S);
}

void heapify(pt t){
	if(!t) 
		return;
	pt opt = t;
	if(t->c[0] && t->c[0]->prior > opt->prior){
		opt = t->c[0];
	}
	if(t->c[1] && t->c[1]->prior > t->prior){
		opt = t->c[1];
	}	
	if(opt != t){
		swap(t->prior, opt->prior);
		heapify(opt);
	}
}

pt build(const vi & v, int l , int r){
	if(l > r)
		return nullptr;
	int mid = l + (r-l)/2;
	pt t = new node(v[mid]);
	t->c[0] = build(v,l,mid-1);
	t->c[1] = build(v,mid+1,r);
	heapify(t);
	upd(t);
	return t;
}

void add(int pos , const vi &c){ // insert after pos	
	auto p = split(t, pos);
	pt nt = build(c,0,sz(c)-1);
	t = merge(merge(p.F, nt), p.S);
}


int get_sum(int pos , int tot){
	auto p = split(t, pos-1);
	auto z = split(p.S, tot);
	int ans = 0;
	prop(z.F);
	if(z.F){
		ans = z.F->sum;
	}
	p.S = merge(z.F, z.S);
	t = merge(p.F, p.S);
	return ans;
}

int max_sum(){
	int ans = 0;
	t = upd(t);
	if(t){
		ans = t->bst;
	}
	return ans;
}
