/* Checks if a point is inside a Polygon, dont needs to be convex
 * Better usages with long long
 * Source: https://vlecomte.github.io/cp-geo.pdf , page 61
 * Status: Weakly tested on ASC 1, problem F
*/

#include "Point.h"
#include "OnSegment.h"


bool above(P a,P p){
	return p.y >= a.y;
}

bool crossesRay(P a,P p,P q){ // segment p->q vs horizontal ray, a -> inf
	return (above(a,q) - above(a,p))*sgn(a.cross(p,q)) > 0;
}

bool inPolygon(vector<P>& poly,P A,bool strict = true){ // checks if A is inside poly
	int cnt = 0;
	for(int i=0,n = sz(poly);i<n;i++){
		if(onSegment(poly[i],poly[(i+1)%n],A)){
			return !strict;
		}
		cnt+= crossesRay(A,poly[i],poly[(i+1)%n]);
	}
	return cnt&1;
}
