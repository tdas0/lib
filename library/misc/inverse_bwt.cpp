// Invert BWT
// Given a Burrows-Wheeler Transform, return the original string
// BWT(S) = concat of last chars of sorted array of every cyclical rotation of S
// {abcd , dabc , cdab , bcda}
// sorting : 
// {abcd , bcda , cdab , dabc}
// BWT(abcd) = dabc

string inverse_bwt(string s){
	vector<pair<int,int>> v;
	for(int i = 0 ; i < (int) s.size() ; i ++)
		v.push_back({s[i] , i});
	sort(v.begin() , v.end());
	int pos = (int) s.size() - 1;
	string S;
	for(int i = 0 ; i < (int) s.size(); i ++){
		S += s[pos = v[pos].second];
	}
	return S;
}
