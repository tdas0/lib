/**
 * Author: Naim
 * Date: 2020-03-19
 * Description: Acha o tamanho do maior palindromo de tamanho par/impar começando em i;
 * d1 -> tamanho impar - d1[i] = x significa que ele tem tamanho 2x -1 com centro em "i"
 * d2 -> tamanho par - d2[i] = x tem tamanho 2x sendo q uma metade vai de [i,i+x-1] e a outra de [i-x,i-1]
 * Time: O(N)
 * Status:tested
 */

vector<int> d1(n),d2(n);
	for(int i=0,l=0,r=-1;i<n;i++){
		int k = (i>r) ? 1 : min(d1[l+r-i],r-i+1);
		while(0<=i-k && i+k<n && s[i-k]==s[i+k]){
			k++;
		}
		d1[i] = k--;
		if(i+k>r){
			l = i-k;
			r = i+k;
		}
	} //palindromo de tamanho impar;
	
	for(int i=0,l=0,r=-1;i<n;i++){
		int k = (i>r) ? 0 : min(d2[l+r-i+1],r-i+1);
		
		while(0<=i-k-1 && i+k<n && s[i-k-1]==s[i+k]){
			k++;
		}
		d2[i] = k--;
		if(i+k>r){
			r = i+k;
			l = i-k-1;
		}
	} //palindromo de tamanho par;
