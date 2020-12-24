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
// ans = somatorio ( (-1)^i * (k choose i) * (k-i)^n)
ll get(int n, int k){
	ll ans = 0;
	vector<ll> choose(k+1);
	choose[0] = 1;
	for(int j = 1; j <= k; j++){
		choose[j] = (choose[j-1] * (k-j+1)) % mod;
		choose[j] = (choose[j]*poww(j, mod-2))%mod;
	}
	for(int i = 0; i<= k; i++){
		ll S = (i%2 == 0 ?1:-1);
		S = S*choose[i]*poww(k-i, n);
		S %= mod;
		if(S<0)S += mod;
		ans += S;
		ans %= mod;
	}
	return ans;
}

// N^2 approach to  Stirling numbers of the second kind
  for (int i = 1; i <= n; i++) 
     for (int j = 1; j <= i; j++) 
       if (j == 1 || i == j) 
          dp[i][j] = 1; 
       else
          dp[i][j] = (1ll*j * dp[i - 1][j] + dp[i - 1][j - 1])%mod; 
  
 dp[n][k] -> numero de particoes dos numeros 1...n em K grupos nao vazios (assumindo n>=k)  
