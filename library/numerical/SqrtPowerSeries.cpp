/**
  * Author: Naim
  * Status: tested on yosopu, 1.2s for N<=5e5
  * Description: Finds the Sqrt of a Formal Polynomial Series
  * Useful for GF, such as Cattalan Number
  * C(X) = (1 - sqrt(1 - 4x))/(2x)
  * Complexity: O(Nlog^2N)
  */
// #include "./InversePowerSeries.cpp"
// #include number-theory/ModSqrt.cpp
vl sqrtSeries(vl A,int n){
    int deg = 0;
    while(deg < sz(A) && A[deg]==0)deg++;
    if(deg == sz(A)){
        return A;
    }
    if(deg&1){
        cout << -1 << endl;
        exit(0);
    }
    A = vl(A.begin()+deg,A.end());

    vl cur = {sqrt(A[0],mod)};
    ll inv2 = modpow(2,mod-2,mod);

    int N = 1;
    // cur_{2N} = 1/2(cur_N + A/cur_N)
    while(N < n){
        N*=2;
        vl invCur = inverse(cur,N);
        vl B = fix(conv(fix(A,N),invCur),N);
        for(int i=0;i<sz(B);i++){
            B[i] += (i < sz(cur) ? cur[i] : 0);
            B[i] = B[i]%mod * inv2%mod;
        }
        cur = B;
	  }
    cur.insert(begin(cur),deg/2,0);
    return fix(cur,n);
}
