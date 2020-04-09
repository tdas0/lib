/**
 * Author: Tiago
 * Source: bqi
 * Date: 2020-04-09
 * Description: Divide and Conquer dynacon com eventos 0 index, comentarios no codigo, não mudar ordem das coisas :) 
 * Time: Both operations are $O(\log N)$.
 */


template <class T>
struct dcq{
	vector<vector<T>> st; int n;
	dcq(int n ) : st(2*n , vector<T>()) , ans(n) ,  n(n){}
	void upd(int x , int y , T q){ //evento Q em [X,Y] (eventos 0 index)
		for(x += n, y += n+1; x < y ; x/=2 , y/=2){
			if(x&1) st[x++].push_back(q);
			if(y&1) st[--y].push_back(q);
		}
		return;
	}
	void solve(int curr = 1){
		allin(w, st[curr]){
			// adiciona as coisas
		}
		if(curr >= n){
			// responde em ans[curr -n]
		}
		else{
			solve(2*curr) ; solve(2*curr+1);
		}
		// da roll back
		return ;
	}	
};