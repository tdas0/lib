/* Descricao: Permite fazer "bitmask" para bases > 2
 * Get Mask pega o valor na i-esima posicao de mask na base K
 * Tested on http://opentrains.snarknews.info/~ejudge/sn_sh.cgi?data=result_team&sid=5971f41c589840b9
 */
 
 const int k = ;//base
 int powk[logk]; // powk[i] = pow(k,i) 

 int get_mask(int mask, int i){
	return (mask/powk[i]) % k;
}

// exemplo: SOS - cnt(v) = soma de Ai onde todo bit não nulo de i é igual ao de v (v contem i)

rep(j,0,m)rep(mask,1,p3[m]){ // p3 -> potencias de 3 (problema C da CCPC 2016/2017 finals
    int here = (mask/p3[j])%3;
    if(here == 0)continue;
    int nv = mask - here * p3[j];
    cnt[nv]+=cnt[mask];
  }
