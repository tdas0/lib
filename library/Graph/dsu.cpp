/**
 * Author: Tiago
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		rep(i,0,n+1) p[i] = i;
	}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};	