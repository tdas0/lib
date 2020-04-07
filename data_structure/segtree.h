
/**
 * Author: Tiago
 * Source: kactl
 * Description: Segtree sem lazy, 0 index, ST<T> seg(tamanho , elemento inicial), criar uma classe T 
 * o merge dela deve ser o operador +
 * iniciar a segtree com tamanho e o elemento inicial (se for max, -inf, se for min + inf , .. etc)
 * 0 INDICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Time: O(\log N)
 * Status: stress-tested
 */

struct node{
	pll x;
	node operator+(const node &rhs) const{ // exemplo de operator
		if(x.first > rhs.x.first) return *(this);
		return rhs;
	}
};
template <class T>
struct ST{
	vector<T> st; int n; 
	T ini; 
	ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
	void upd(int pos, T val){ // pos -0 index
		for(st[pos += n] = val ; pos /= 2;)
			st[pos] = st[2*pos] + st[2*pos + 1];
	}
	T query(int x , int y){ // x e y - 0 index
		T ra = ini , rb = ini;
		for(x += n, y += n ; x < y ; x/=2 , y/=2){
			if(x&1) ra = ra + st[x++];
			if(y&1) rb = rb + st[--y];
		}
		return ra + rb;
	}
};