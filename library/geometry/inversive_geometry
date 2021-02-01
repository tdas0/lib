/**
 * Author: Matheus Leal
 * Date: 31/01/2021
 * Description:
   IMPORTANTE: Um bom raio para evitar overflow ou precisao é sqrt(dmin * dmax)
   
	 Dado uma circumferencia C de centro O e raio R e um ponto P, retornar o inverso de P utilizando C como referencia.
   OP*OP' = r^2
   O inverso de um ponto que toca a circunferencia nao eh alterado
   se O = P -> Inverso eh infinito, entao temos uma circunferencia centrada em infinito (uma reta), onde a parte interna eh um semiplano
   que nao possui o centro O dentro
 * Status: tested with 40th Petrozavodsk camp - day2 F. Friendship circles
 * Time: O(n \log n)
*/
#pragma once

#include "Point.h"

//Modificar
typedef Point<long double> P;

long double dist(P a, P b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y - b.y)*(a.y-b.y));
}

//NUNCA PERGUNTAR O INVERSO DE P
P InversiveFromCircle(P o, long double r, P p) {
	assert(!(o == p));
	long double OP = dist(o, p);
	long double OP1 = (r*r)/OP;
	long double c = OP1/OP;
	P q = P(c*(p.x - o.x) + o.x, c*(p.y - o.y) + o.y);
	return q; 
}
