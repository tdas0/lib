/**
 * Author: ..
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: erdos gallai, graph realization by degree sequence
 * Time: 
 */
bool erdosgallai(vector<int> d){
	sort(d.rbegin() , d.rend());
	vector<long long> ds(d.size());
	int  n = d.size() , p = n - 1;
	for(int i = 0 ; i < n; i ++){
		if(i) ds[i] = ds[i-1] + d[i];
		else ds[i] = d[i];
	}
	for(int k = 1 ; k <= n; k ++){
		while(p>=0 && d[p] <k) p--;
		long long soma;
		if(p >= k - 1){
			soma = (p - k + 1)*1ll*k + ds[n-1] - ds[p];
		}
		else soma = ds[n-1] - ds[k-1];
		if(ds[k-1] > k*(k-1LL) + soma) return false;
	}
	return ds[n-1]%2 == 0;
}
