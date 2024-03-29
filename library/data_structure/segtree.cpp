
/**
 * Author: Tiago
 * Source: kactl
 * Description: Segtree sem lazy, 0 index, ST<T> seg(tamanho , elemento inicial), criar uma classe T 
 * o merge dela deve ser o operador +
 * iniciar a segtree com tamanho 
 * 0 INDICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Time: O(\log N)
 * Status: stress-tested
 */
struct node{
	pll x;
	node operator+(const node &rhs) const{  // exemplo de operador de merge
		if(x.first >= rhs.x.first) return {x};
		return rhs;
	}
};
template <class T>
struct ST{
	vector<T> st; int n; 
	ST(int n) : st(2*n) , n(n){}
	void upd(int pos, T val){ // pos 0index
		for(st[pos += n] = val ; pos /= 2;)
			st[pos] = st[2*pos] + st[2*pos + 1];
	}
	T query(int x , int y){ // [x,y] , x, y -0index
		T ra , rb;
		bool okl = false, okr = false;
		for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
			if(x&1) ra = (okl ? ra + st[x] : st[x]) , x++ , okl = true;
			if(y&1) --y , rb = (okr ? st[y] + rb : st[y]) , okr = true;
		}
		return (okl ? (okr ? ra + rb : ra): rb);
	}
};

/* BUILD O(N) - opcional:
void build() { // no inicio st[i+n] = a[i], 0 <= i < n
        for (int i = n - 1; i > 0; --i) st[i] = st[i * 2] + st[i*2 + 1];
}
*/
