/**
 * Author: Tiago Domingos
 * Date: 14/02/2020
 * Description:
	Given two convex polygons (ccw, sorted by polar angle by the min lex.)
	return the minkowski sum of the two of then (if a is an vector in A, b in B, A^B contains (a+b))
	It may contain collinear points, but can easily be treated while making the minkowski sum
 * Status: not-tested 
 * Time: O(n + m)
*/

#pragma once
typedef Point<ll> P;
vector<P> minkowski(const vector<P> &A ,const vector<P> &B){
	vector<P> e;
	e.push_back(A[0] + B[0]);
	int i = 0 , j = 0 ;
	auto comp = [&](P a , P b){
		int hp1 = (a.x < 0 || (a.x == 0 && a.y < 0)) , hp2 = (b.x < 0 || (b.x == 0 && b.y < 0));
		if(hp1 != hp2) return hp1 < hp2;
		if(a.cross(b) != 0){
			return a.cross(b)  > 0;
		}
		return a.dist2() < b.dist2();
	};
	while(i != sz(A) || j != sz(B)){
		P a = A[(i+1)%sz(A)] - A[i] , b = B[(j+1)%sz(B)] - B[j];
		if(i == sz(A)) e.push_back(e.back() + b) , j++;
		else if(j == sz(B)) e.push_back(e.back() + a), i++;
		else{
			if(comp(a,b)) e.push_back(e.back() + a) , i++;
			else e.push_back(e.back() + b) , j ++;
		}
	}
	e.pop_back();
	return e;
}
// warning : e contains colinear points, you can easily remove in the merge step 
