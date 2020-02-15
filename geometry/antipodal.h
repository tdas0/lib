/**
 * Author: Tiago Domingos
 * Date: 14/02/2020
 * Description: Returns the two points with max distance on a convex hull 
 * Status: kattis roberthood
 */
#pragma once

typedef Point<ll> P;
array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ll, array<P, 2>> res({0, {S[0], S[0]}});
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}