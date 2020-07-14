/**
 * Author: Leal
 * Date: 2020-03-19
 * Description: Dado um texto S e um padrao P. responde em quais posicoes P aparece em S.
 * B[i] = maior j, tal que s[0]...s[j-1] = s[i-j-1]...s[i-2]
 * Time: O(N + M)
 * Status:tested
 */

struct kmp{
	vector<int> b, pos;
	string s, p;
	//A = texto, B = padrao
	void build(string A, string B){
		s = A, p = B;
		int n = sz(s), m = sz(p);
		b.resize(m + 1);
		b[0] = -1;
		for(int i = 0, j = -1; i < m; i++) {
			while(j >= 0 and p[i] != p[j]) j = b[j];
			j ++;
			b[i + 1] = j;
		}

		//achar posicoes onde o padrao aparece
		for(int i = 0, j = 0; i < n; i++){
			while(j >= 0 and s[i] != p[j]) j = b[j];
			j ++;
			if(j == m) pos.push_back(i - j + 1);
		}
	}
	void clear(){
		s="", p="";
		pos.clear();
		b.clear();
	}
} KMP;
