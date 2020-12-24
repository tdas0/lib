#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
//#define int long long
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;



void coloca(string &s,int& tam,set<string>&S,string x,int id){

	if(id==s.size())return;

	string cur = x;
	cur+=s[id];
	if(cur.size()==tam)
		S.insert(cur);
	else{
		coloca(s,tam,S,cur,id+1);
	}
	coloca(s,tam,S,x,id+1);

}

int ok(string s,string t,int tam){

	set<string> S1,S2;
	string x="";
	coloca(s,tam,S1,x,0);
	coloca(t,tam,S2,x,0);


	for(auto it : S1){
		if(S2.find(it)==S2.end())return false;
	}
	return true;

}

int tenta(string s,string t){

	for(int i=2;i<=s.size();i++){
		if(!ok(s,t,i))return i;
	}
	return -1;
}


void go(int n){
	string s="",t="";

	for(int j=0;j<n;j++){
		s+='a';
		t+='a';
	}

	for(int i=0;i<n;i++){
		s+='b';
		t+='b';
	}
	
//	cout <<s <<" "<<t <<endl;

	int best = 0;

	do{

		do{
				//cout << s <<" "<<t<<" "<<tenta(s,t)<<endl;
				int x = tenta(s,t);
				if(x > best){
					best =x;
					//cout <<s << " "<<t<<" "<<x<<endl; 
				}else if(x==best){
					//cout<<s<<" "<<t<<" "<<x<<endl;
				}
				if(x==2*n){

				}

		}while(next_permutation(t.begin(),t.end()));

	}while(next_permutation(s.begin(),s.end()));
	cout << n<<" "<<best << endl;
}

int32_t main(){
	fastio;
	/*
	for(int i=1;i<=4;i++){
		go(i);
	}
	*/
	int n;
	cin>>n;
	string s="";
	string t="";
	int sz = 2*n;
	for(int i=0;i<n;i++)s+='a';
	for(int i=0;i<n;i++)s+='b';

	for(int i=0;i<n-1;i++)t+='a';
	t+="ba";
	for(int i=0;i<n-1;i++)t+='b';
	cout <<s<<endl;
	cout<<t<<endl;
	



}