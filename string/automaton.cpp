/**
 * Author: Tiago
 * Date: 2020-03-28
 * Description: Faz um DFA minimal tal que seguindo um caminho do inicio a gente tem todas as substrings da string
 * mudar alpha e first pra extender o alfabeto
 * online e permite adição de char
 * Time: O(tamanho*alfabeto)
 * Status:tested
 */
struct suffix_automaton{
	enum{alpha  = 26 , first = 'a'};
	struct node{
		int len, link;
		vi next;
		node(int x , int y , int v){
			len = x , link = y;
			next = vi(alpha);
			rep(i,0,alpha) next[i] = v;
		}

	};
	ll substrings = 0; int last = 0 ;
	vector<node> st; 
	suffix_automaton(int v = 0){st.push_back(node(0,-1,0));}
	void extend(char c){
		c -= first;
		int cur = sz(st) , p,q;
		st.push_back(node(st[last].len + 1,-1,0));
	    for (p=last; p!=-1 && !st[p].next[c]; p=st[p].link) st[p].next[c] = cur;				
		if(p == -1) st[cur].link = 0 ,substrings += st[cur].len;
		else{
			q = st[p].next[c];
			if(st[p].len + 1 == st[q].len){
				st[cur].link = q;
				substrings += st[cur].len - st[q].len;
			}
			else{
				int clone = sz(st);
				st.push_back(node(st[p].len+1,st[q].link,0));
				st.back().next = st[q].next;
	            substrings += st[clone].len - st[st[clone].link].len;
	            for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
	                st[p].next[c] = clone;
	            substrings -= st[q].len - st[st[q].link].len;
	            st[q].link = st[cur].link = clone;
	            substrings += st[q].len - st[st[q].link].len + st[cur].len - st[st[cur].link].len;
			}
		} 
		last = cur;
	}
	vi terminal(){
		int p = last; vi t;
		while(p >= 0){
			t.push_back(p), p = st[p].link;
		}
		return t;
	}
};