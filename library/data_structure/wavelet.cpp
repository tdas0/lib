/**
 * Author: Naim
 * Source: Common knowledge(?)
 * Description: O vetor dado para inicializar deve ser 0-indice. O resto é 1-indice
 * Se comprimir fica melhor. "b" é o array com a soma de prefixos de v[i]<=mid
 * Para updates mudar o "b" em cada nó para uma BIT...
 * Time: Build O(NlogV), Querys O(logV)
 * Status: stress-tested
 */
 
struct Wavelet{
 	// se der é melhor comprimir!
	int MINV = 1e9,MAXV = -1e9;
	vi v;
	vector<vi> b;
	vi fL,fR;
	int cur;
	Wavelet(vi vec){ // 0-indice
		b.pb(vi());b.pb(vi());
		fL = fR = vi(2,0);
		for(int i : vec)MINV = min(i,MINV),MAXV = max(MAXV,i);
		cur=1;

		build(1,MINV,MAXV,vec);
		v = vec;
	}
	void build(int no,int L,int R,vi& vec){
		if(sz(vec) == 0 || L>R)return;
		b[no] = vi(sz(vec) + 1,0);
		int mid = L + (R-L)/2;
		vi l,r;
		rep(k,0,sz(vec)){
			b[no][k+1] = b[no][k];
			if(vec[k]<=mid)b[no][k+1]++,l.pb(vec[k]);
			else r.pb(vec[k]);
		}
		fL[no] = fR[no] = 0;
		if(L==R)return;
		if(sz(l)){
			fL.pb(0);fR.pb(0);b.pb(vi());
			fL[no] = ++cur;
			build(fL[no],L,mid,l);
		}
		if(sz(r)){
			fL.pb(0);fR.pb(0);b.pb(vi());
			fR[no] = ++cur;
			build(fR[no],mid+1,R,r);
		}
	}
	int count(int no,int i,int j,int x,int L,int R){
		if(!no)return 0;
		if(L == R){return j-i;}
		int mid = L + (R-L)/2;
		int ei = b[no][i],ej = b[no][j];
		if(x<=mid)return count(fL[no],ei,ej,x,L,mid);
		ei = i - ei,ej = j - ej;
		return count(fR[no],ei,ej,x,mid+1,R);
	}
	// numero de ocorrencias de x em [l,r]
	int count(int l,int r,int x){
		if(x<MINV || x>MAXV)return 0;
		return count(1,l-1,r,x,MINV,MAXV);
	}
	int kth(int no,int i,int j,int k,int L,int R){
		if(L == R)return L;
		int mid = L + (R-L)/2;
		int ei = b[no][i],ej = b[no][j];
		int cnt = ej-ei;
		if(k<=cnt)return kth(fL[no],ei,ej,k,L,mid);
		ei = i - ei,ej = j - ej;
		return kth(fR[no],ei,ej,k-cnt,mid+1,R);
	}
	// kth no intervalo [l,r] ( 1-indice !!! )
	int kth(int l,int r,int k){
		return kth(1,l-1,r,k,MINV,MAXV);
	}
	void Swap(int no,int i,int v1,int v2,int L,int R){
		if(L == R)return;
		int mid = L + (R-L)/2;
		if(v1<=mid and v2 > mid){
			b[no][i]--;
		}else if(v1>mid and v2<=mid){
			b[no][i]++;
		}else{
			int ei = b[no][i];
			if(v1 <= mid)
				return Swap(fL[no],ei,v1,v2,L,mid);
			ei = i - ei;
			Swap(fR[no],ei,v1,v2,mid+1,R);
		}
		return;
	}
	// troca i com i+1
	void Swap(int i){
		Swap(1,i,v[i-1],v[i],MINV,MAXV);
		swap(v[i-1],v[i]);
	}
};
