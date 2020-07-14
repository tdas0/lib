/**
 * Author: Naim
 * Date: 2020-03-24
 * License: CC0
 * Source:
 * Description: Distance Point to things
 * Status: tested (maybe need stronger cases (??))
 */
#include "Point.h"

typedef Point<double> P;
const double EPS = 1e-9;
P projectPointLine(P a,P b,P p){
	// to = M.(P-B)/(M.M);
	return a + (b-a)*((b-a).dot(p-a))/((b-a).dot(b-a));
}
double distPointLine(P p,P a,P b){
	return (p-projectPointLine(a,b,p)).dist();
}
double distPointRay(P p,P a,P b){
	P B = a,M = b-a;
	// Line on the form L(t) = B + Mt ,t >=0;
	double to = M.dot(p - B)/M.dot(M);
	
	if(to<=EPS){
		return (B-p).dist();
	}
	return (p-(B+M*to)).dist();
}

double distPointSegment(P p,P a,P b){
	if(a==b)return (a-p).dist();
	P B = a,M=b-a;
	double to = M.dot(p-B)/M.dot(M);
	if(to<=EPS){// before 'a'
		return (p-B).dist();
	}else if(to>=1.0+EPS){//after 'b'; 
		return (p-(B+M)).dist();
	}else{// projection
		return (p-(B+M*to)).dist();
	}
	// can use to project Point in segment
}

pair<P,P> generatePoint(double a,double b,double c){
  // given a Line return two points to use in above functions
	if(b==0){
		return make_pair(P(-1.0*c/a,0),P(-1.0*c/a,1));
	}
	return make_pair(P(0,-1.0*c/b),P(1,1.0*(-a-c)/b));
}
