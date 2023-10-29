#include <bits/stdc++.h>
using namespace std;

int bad(char c1,char c2){
	if(c1 == ')' && (c2 == '(' || c2=='a'))return 1;
	if(c1 == '(' && (c2 ==')' || c2=='+'))return 1;
	if(c1 == 'a' && c2=='(')return 1;
	if(c1 == '+' && (c2=='+' || c2==')'))return 1;
	return 0;
}
long long res=0;

void solve(string& s){
	stack<int> st;
	st.push(0);
	for(auto ch : s){
		if(ch == '+')continue;
		if(ch == 'a')st.top()++,res += st.top();
		else if(ch == '('){
			st.push(0);
		}else{ // )
			if(st.size()==1){st.pop(),st.push(0);continue;}
			res++;
			st.pop();
			res+=st.top(),st.top()++;
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	string cur="";
	for(auto &ch : s){
		if(ch>='a' && ch<='z')ch = 'a';
		else if(ch == '(' || ch == ')')ch = ch;
		else ch = '+';
		if(cur.size() && bad(cur.back(),ch)){
			solve(cur);cur.clear();
		}
		if(cur.size()==0 && ch ==')')continue;
		cur+=ch;
	}
	solve(cur);
	cout<<res<<endl;	
}
