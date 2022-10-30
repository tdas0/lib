/**
 * Author: tdas
 * Description: Tiago explica. 0 indexado
*/
#define pt node*
struct node{
	int v,sum,sz,lz,prior; 
	bool lazy , flip;
	pt c[2];
	node(int v){
		c[0] = c[1] = nullptr;
		this->v = sum = v , lz = 0 , sz = 1 , prior = rng();
		lazy = flip = 0;
	}
	~node(){
		delete c[0];
		delete c[1];
	}
};
pt t = nullptr;
int getsz(pt t){
	if(!t)return 0;
	return t->sz;
}
void prop(pt &t){
	if(!t)return;
	if(t->flip){
		t->flip = false;
		swap(t->c[0] , t->c[1]);
		rep(i,0,2) if(t->c[i]){
			t->c[i]->flip ^= 1;
		}
	}
	if(t->lazy){
		t->v = t->lz;
		t->sum = getsz(t) * t->lz ; 
		rep(i,0,2) if(t->c[i]){
			t->c[i]->lazy = 1 , t->c[i]->lz = t->lz;
		}
		t->lz = 0 , t->lazy = 0;
	}
}
pt upd(pt t){
	if(!t)return t;
	prop(t);
	t->sz = 1;
	t->sum = t->v;
	if(t->c[0]){
		prop(t->c[0]);
		t->sum = t->c[0]->sum + t->sum;
		t->sz += t->c[0]->sz;
	}	
	if(t->c[1]){
		prop(t->c[1]);
		t->sum = t->sum + t->c[1]->sum;
		t->sz += t->c[1]->sz;
	}
	return t;
}

// joga k caras na arvore da esquerda
pair<pt,pt> split(pt t , int k){
	if(!t)return {t,t};
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
void modify(int pos, int tot, int c){
	auto p = split(t, pos-1);
	auto z = split(p.S , tot);
	if(z.F)z.F->lazy = 1 , z.F->lz = c;
	p.S = merge(upd(z.F) , z.S);
	t = merge(p.F , p.S);
}
void reverse(int pos , int tot){
	auto p = split(t, pos-1);
	auto z = split(p.S , tot);
	if(z.F)z.F->flip ^= 1;
	p.S = merge(upd(z.F) , z.S);
	t = merge(p.F, p.S);
}
