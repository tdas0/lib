/**
 * Author: Tiago Domingos
 * Date: 14/02/2020
 * Description:
	Return points in CCW order, using graham scan, if you want collinears, change <= to < in the pop_back part and 
	remove (hull[back] == hull[0]) part
 * Status: tested with Kattis problems convexhull 
 * Time: O(n \log n)
*/
#pragma once

#include "Point.h"

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	P pivot = pts[0];
	rep(i,0,sz(pts)) pivot = min(pivot , pts[i]);
	sort(all(pts) , [&](P a , P b){
		a = a - pivot , b = b - pivot;
		int hp1 = a < P(0,0) , hp2 = b < P(0,0);
		if(hp1 != hp2) return hp1 < hp2;
		if(a.cross(b) != 0){
			return a.cross(b)  > 0;
		}
		return a.dist2() < b.dist2();
	});
	vector<P> hull;
	rep(i,0,sz(pts)){
		while(hull.size() > 1 && ((hull.back() - hull[sz(hull) - 2]).cross(pts[i] - hull.back()) <= 0)) hull.pop_back();
		hull.push_back(pts[i]);
	}
	if(hull.back() == hull[0]) hull.pop_back();
	return hull; 
}
