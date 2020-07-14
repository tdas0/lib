/**
 * Author: Naim
 * Date: 2020-03-30
 * License: CC0
 * Description: Dado um Circulo de centro C, Raio R e um ponto P FORA do circulo
 * Acha os pontos p1,p2 tal que o segmento p1,p e p2,p sao tangentes ao circulos
 * Ideia: Acha o angulo que vai ter entre p e p1 usando seno, pega o vetor de tamanho dist e
 * rotaciona
 * Status: tested em "Avoid the Circle"
 */
pair<P,P> tangentCircl(P C,double R,P p){
    if(abs(sq(C.x-p.x) + sq(C.y-p.y) - R*R ) < EPS){
        return {p,p};
    }
    double dist = (C-p).dist();
    double ang = asin(R/dist);
    double distancia = sqrt(sq(dist) - sq(R));
    P p1 = (C - p);
    p1 = p1.unit();
   
    p1 = p1*distancia;
    P p2 = p1;
    p1 = p + p1.rotate(-ang);
    p2 = p + p2.rotate(ang);
 
    return {p1,p2};
}
