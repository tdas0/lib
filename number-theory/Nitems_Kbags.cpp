/**
 * Author: Matheus Leal
 * Date: 2020-01-11
 * Description: Numero de maneiras de colocar N objetos em K mochilas onde cada mochila tem pelo menos 1 objeto
 * choose[j] = K escolhe j
 * poww(a, b) = a^b
 * Time: O(K*log(K))
 * Status:tested
 */
 
//Numero de maneiras de colocar N objetos em K mochilas
//considerando que cada mochila tem pelo menos 1 objeto
//choose[i] = choose(k, i) = k escolhe i
// ans = somatorio ( (-1)^i * (k choose i) * (k-1)^n)
int get(int n, int k){
	int ans = 0;
	vector<int> choose(k+1);
	choose[0] = 1;
	for(int j = 1; j <= k; j++){
		choose[j] = (choose[j-1] * (k-j+1)) % mod;
		choose[j] = (choose[j]*poww(j, mod-2))%mod;
	}
	for(int i = 0; i<= k; i++){
		int S = (i%2 == 0 ?1:-1);
		S = S*choose[i]*poww(k-i, n);
		S %= mod;
		if(S<0)S += mod;
		ans += S;
		ans %= mod;
	}
	return ans;
}
