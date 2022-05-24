/**
 * Author: Simon Lindholm
 * Date: 2016-08-27
 * License: CC0
 * Source: own work
 * Description: Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily.
 *  Returns rank, or -1 if no solutions. Destroys $A$ and $b$.
 * Funciona em Z/Zp ou qualquer campo com inverso existente
 * !!! Cuidado com ll vs int
 * Time: O(n^2 m)
 * Status: bruteforce-tested for n, m <= 4
 */
int mod = 13;
int modinv(int x){
	return modpow(x , mod - 2 , mod);
}
int solveLinear(vector<vi>& A, vi& b, vi& x) {
	rep(i,0,sz(A)){
		rep(j,0,sz(A[i])){
			A[i][j] = ((A[i][j])%mod + mod)%mod;
		}
	}
	rep(i,0,sz(b)){
		b[i] = (b[i]%mod + mod)%mod;
	}
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	vi col(m); 
	for(int i = 0 ; i < sz(col) ; i++) col[i] = i;
	rep(i,0,n) {
		int v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		rep(j,i,n) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		rep(j,i+1,n) {
			int fac = (A[j][i] * bv) % mod;
			b[j] = ((b[j] - fac * b[i]) % mod + mod)%mod;
			rep(k,i+1,m) A[j][k] = ((A[j][k] - fac*A[i][k]) % mod + mod)%mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		rep(j,0,i)
			b[j] = ((b[j] - A[j][i] * b[i])%mod + mod)%mod;
	}
	return rank;
}
