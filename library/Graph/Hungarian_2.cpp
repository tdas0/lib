/**
 * Author: 300iq
 * Date: 2020-04-04
 * License: CC0
 * Source: https://codeforces.com/gym/100197/standings
 * Description: Mincost of an assigment such that
 * u[i] + v[j] <= edge(i,j). -v[0] has the answer to the
 * problem. To MaxCost, negate all costs. To recover the answer
 * use u[i] and v[j]. COST are 0-index and u/v are 1-index 
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, tested on ASC2-F
 * Other implementarions: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/WeightedMatching.h#L39
 */
 
 ll hungarian(vector<vi> cost){ // cost 0-index
  // hungarian from 300iq
    int INF = ;// ?? 1e9 pra int 
    int n = sz(cost),m = sz(cost[0]);
    assert(n<=m);

    vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
    // 1-index ^
   
    for (int i=1; i<=n; ++i) {
            p[0] = i;
            int j0 = 0; // dummy variable
            vector<int> minv (m+1, INF);
            vector<char> used (m+1, false);
            do {
                used[j0] = true;
                int i0 = p[j0],  delta = INF,  j1;
                for (int j=1; j<=m; ++j)
                    if (!used[j]) {
                        int cur = cost[i0 - 1][j - 1]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
    

  return -v[0];
}
