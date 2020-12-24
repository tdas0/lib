#include <bits/stdc++.h>
using namespace std;

int main(){
	int a;
	cin>>a;
	string l;
	cin>>l;
	string s;
	getline(cin,s);

	if(l=="G"){
		cout<<"OK"<<endl;
	}else if(l=="PG"){
		if(a<13)cout<<"OK IF ACCOMPANIED"<<endl;
		else cout<<"OK"<<endl;
	}else if(l=="R-13"){
		if(a<13)cout<<"ACCESS DENIED"<<endl;
		else cout<<"OK"<<endl;
	}else if(l=="R-16"){
		if(a<16)cout<<"ACCESS DENIED"<<endl;
		else cout<<"OK"<<endl;
	}else{
		if(a<18)cout<<"ACCESS DENIED"<<endl;
		else cout<<"OK"<<endl;
	}

}