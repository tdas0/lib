/**
 * Author: Tiago Domingos
 * Date: 2020-01-11
 * Description: Multiplicative Functions Container
   Calculate functions such $f(1) = 1$ , $f(p^k)$ is something we know and $f(i*p) = f(i) * f(p)$ if 
   $\gcd(i,p) = 1$ using linear sieve
 * Time: O(N)
 * Usage: Change multiplicative::T() to the function definition and do init(), multiplicative::get(x) is 
   equal to f(x)
 * Status:tested
 */
class multiplicative{
public:
	int T(int p , int k , int pk){
		return pk - pk/p ;
	}
	void sieve(int n){
		for(int j = 2 ; j < n ; j++){
			if(!is_composite[j]) primes.push_back(j) , cnt[j] = 1 , sp[j] = j , func[j] = T(j , cnt[j] , j);
			for(int i = 0 ; i < primes.size() && primes[i]*j < n ; i++){
				is_composite[primes[i]*j] = true;
				if(j%primes[i] == 0){
		 			cnt[primes[i]*j] = cnt[j] + 1 , sp[primes[i]*j] = sp[j] * primes[i]; 
		 			func[primes[i]*j] = func[j/sp[j]] * T(primes[i] , cnt[j]+1, sp[primes[i]*j]);  
					break; 
				} 
				else{
					func[primes[i]*j] = func[primes[i]] * func[j] ; 
					cnt[primes[i] * j] = 1 , sp[primes[i]*j] = primes[i] ;  
				}
			}
		}
	}
	void init(int n){
		is_composite.assign(n,0),cnt.assign(n,0),func.assign(n,0) , sp.assign(n,0), func[1] = 1;
		sieve(n);
	}
	inline int get(int x){
		return func[x];
	}
private: 
	vector<bool> is_composite; vector<int> primes , cnt , func , sp; // func is value of multiplicative 
	// cnt is expoent of smallest prime factor, sp is smallest_prime ^ cnt
};