/* 
 * Tecnicas para problemas de decomposição em raiz
 * Adicionem ai o que acharem conveniente
 */

// Tested on XX Open Cup named after E.V. Pankratiev. Grand Prix of SPb - D

// Pegar os blocos que estão completos
// se lx > rx não tem nenhum completo
pii get(int l,int r){
    int lx = (l+sq-1)/sq;
    int rx = (r+1)/sq - 1;
    return pii(lx,rx);
  }

// retorna o bloco de cada uma das bordas
// ou -1 se a ponta ta num bloco cheio
pii bordas(int l,int r){
    int lx,rx;
    tie(lx,rx) = get(l,r);
    int L = l/sq,R = r/sq;
    if(L == lx)L=-1;
    if(R == rx || R==L)R=-1;
    return pii(L,R);
}
