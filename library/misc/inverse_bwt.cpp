// Invert BWT (add details)

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
