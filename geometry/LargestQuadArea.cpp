/*
 * Given a Convex Hull, find the area of the biggest Quadrileteral.
 * If the Hull has 3 points, we brute the 4th one ( v has the hull and v2 the original points )
 * O(N**2)
 * Status: Tested
 * Note: Better to use Minkowski (31ms vs 1800ms) , only added because of the two pointers technique 
*/

ll largestAreaQuad(){
	
		if(v.size()<3){
			return 0;
		}
		
		
		if(v.size()==3){
			ll best = 0;
			int n = v2.size();
			for(int i=0;i<n;i++){
				if(v2[i]==v[0] || v2[i]==v[1] || v2[i]==v[2])continue;// only if doesnt have equal points! If it does, use ids
				ll tudo = polygonArea2(v);
				ll op1 = abs(v2[i].cross(v[0],v[1]));
				ll op2 = abs(v2[i].cross(v[0],v[2]));
				ll op3 = abs(v2[i].cross(v[1],v[2]));
				best = max(best,tudo - min({op1,op2,op3}));
			}

			return best;
		}
		
		 n = v.size();
		ll best = 0;	
		for(int i=0;i<n;i++){

			int j = (i+2)%n;
			int l = (i+1)%n;
			int r = (i+3)%n;
			auto next = [&](int j){
				if(j+1>=n)return j+1-n;
				return j+1;
			};
			auto area = [&](int i,int j,int k){
				return abs(v[k].cross(v[i],v[j]));
			};
			while(i!=j){
				while(next(l)!=j && area(i,j,next(l)) >= area(i,j,l)){
					l = next(l);
				}
				
				while(next(r)!=i && area(i,j,next(r))>=area(i,j,r)){
					r =	next(r);
				}
				best = max(best,area(i,j,l) + area(i,j,r));
				j=next(j);
			}


		}

		return best;
}
