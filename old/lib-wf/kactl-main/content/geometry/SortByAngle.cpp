/**
 * Author: Tiago
 * Date: 2021-02-14
 * Description: Sort points by angle arround a chosen pivot, untied by distance
 * Time: $O(n \log n)$
*/

sort(all(pts) , [&](P a , P b){
	a = a - pivot , b = b - pivot;
	int hp1 = a < P(0,0) , hp2 = b < P(0,0);
	if(hp1 != hp2) return hp1 < hp2;
	if(a.cross(b) != 0)return a.cross(b)  > 0;
	return a.dist2() < b.dist2();
});
