/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Projects point p onto line ab. Set refl=true to get reflection
 * of point p across line ab insted. The wrong point will be returned if P is
 * an integer point and the desired point doesn't have integer coordinates.
 * Products of three coordinates are used in intermediate steps so watch out
 * for overflow.
 * Status: stress-tested
  !!! caso dê overflow pode usar a + (b-a) * dot(b-a,c-a)/dot(b-a,b-a) para pegar a projecao de c em a-b;
  Lembrando que isso vem de L(t) = B + M*t, to = M.(P-B)/(M.M) . 
  // para mudar para ray-> to>=0 , para segmento to =[0,1];
 */
#pragma once

#include "Point.h"

template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
