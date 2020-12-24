/* Descricao: Permite fazer "bitmask" para bases > 2
 * Get Mask pega o valor na i-esima posicao de mask na base K
 * Tested on http://opentrains.snarknews.info/~ejudge/sn_sh.cgi?data=result_team&sid=5971f41c589840b9
 */
 
 const int k = ;//base
 int powk[logk]; // powk[i] = pow(k,i) 

 int get_mask(int mask, int i){
	return (mask/powk[i]) % k;
}
