// preencher grid com triominos
#include <iostream>
 
using namespace std;
 
bool f(char g[100][100], int n, int m){
	if(m % 2 == 0){
		string p[3] = {"JJLL", "JKLM", "KKMM"};
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				g[i][j] = p[i % 3][j % 4];
	}
	else if(n % 2 == 0){
		string p[3] = {"EEFF", "EBFD", "BBDD"};
		string q[3] = {"AABB", "ACBD", "CCDD"};
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < 3; j++)
				g[i][j] = p[j][i % 4];
			for(int j = 0; j < m - 3; j++)
				g[i][j + 3] = q[i % 3][j % 4];
		}
	}
	else if(n == 3 or m == 3)
		return false;
	else {
		string p[5] = {"GGIIGHHGG", "GHIGGAHIG", "HHAHHAAII", "GAAIHGHHG", "GGIIGGHGG"};
		
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 5; j++)
				g[i + n - 9][j + m - 5] = p[j][i];
		
		f(g, n - 9, m);
		f(g + n - 9, 9, m - 5);
	}
	
	return true;
}
 
int main(){
	int t, n, m;
	cin >> t;
	
	char g[100][100];
	
	while(t--){
		cin >> n >> m;
		
		bool r = false;
		
		if(n % 3){
			r = true;
			swap(n, m);
		}
		
		if(n % 3 or m == 1 or !f(g, n, m)){
			cout << "NO\n";
			continue;
		}
		
		cout << "YES\n";
		
		if(r)
			for(int i = 0; i < m; i++){
				for(int j = 0; j < n; j++)
					cout << g[j][i];
				cout << endl;
			}
		else
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++)
					cout << g[i][j];
				cout << endl;
			}
	}
}