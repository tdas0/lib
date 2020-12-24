/**
 * Author: Tiago
 * Source: own
 * Desc: Suffix Array nlog^2 sem usar radix sort, bem rápido em prática e independe do tamanho do alfabeto
 * Time: nlog^2 
 * Status: tested : https://codeforces.com/gym/102302/problem/K
 */

template<class T>
struct SuffixArray{
	vi sa,  lcp , inv;
	int n;
	SuffixArray(T & s){
		auto comp = [&](int sz , int pos){
			return pii(inv[pos], ((pos + sz) < sz(inv) ? inv[pos + sz] : -1)); 
		};
		n = sz(s) ;inv = vi(n) , sa = vi(n) , lcp = vi(n);
		rep(i,0,sz(s)) sa[i] = i;
		sort(all(sa) , [&](int a , int b){
			return s[a] < s[b];
		});
		for(int i = 0 , cnt = -1 ; i < n;  i++){
			if(i && s[sa[i-1]] == s[sa[i]]) inv[sa[i]] = cnt ;
			else inv[sa[i]] = ++cnt;
		}
		for(int j = 0 , cnt ; (1<<j) < n; j ++){
			int sz = (1<<j); cnt = -1;  vi newinv(sz(s));
			sort(all(sa) , [&](int a , int b){
				return comp(1<<j , a) < comp(1<<j , b);
			});
			rep(i,0,n){
				if(i && comp(1<<j , sa[i]) == comp(1<<j , sa[i-1])) newinv[sa[i]] = cnt;
				else newinv[sa[i]] = ++cnt;
			}
			swap(newinv, inv);
		}
		rep(i,0,sz(s)) inv[sa[i]] = i;
		int k = 0;
		rep(i,0,n){
			if(inv[i]+1 == n){k = 0 ; continue;}
			int j = sa[inv[i] + 1];
			while(i + k < n && j + k < n && s[i+k] == s[j+k]) k ++;
			lcp[inv[i]] = k;
			k = max(k-1 , 0);
		}
	}
};