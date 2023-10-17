/**
 * Author: YouKnowWho
 * License: CC0
 * Description: Let w(i,j) be the cost function.
 * The required condition is the quadrangle inequality: for all i<=j, w(i,j)+w(i+1,j+1)<=w(i+1,j)+w(i,j+1)
 * it's easier to just list out a few values of w and check then prove.
 * dp[x]=min(dp[k]+w(k,x)) for all k from 0 to x-1.
 * Let k(x) be the optimal index for dp(x).
 * Then for all i<=j, k(i)<=k(j) because of the quadrangle inequality
 * If we can't use CHT for this kind of DP optimization, May try this
 * Status: Tested on 101981B
 * Complexity: $O(N \logN)$
 */

dp[0] = 0;
vector<pair<int, int> > v; // (start pos, best k)
v.push_back(make_pair(0, 0));
for (int x = 1; x <= n; x++) {
int k = (--lower_bound(v.begin(), v.end(), make_pair(x + 1, 0)))->second;
dp[x] = dp[k] + w(k, x);
for (int i = (int)v.size() - 1; i >= 0; i--) {
    int y = v[i].first, oldk = v[i].second;
    if (y > x && dp[x] + w(x, y) < dp[oldk] + w(oldk, y)) v.pop_back();
    else {
    int l = y + 1, r = n + 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (dp[x] + w(x, mid) < dp[oldk] + w(oldk, mid)) r = mid;
        else l = mid + 1;
    }
    if (r != n + 1) v.push_back(make_pair(r, x));
    break;
    }
}
if (v.size() == 0) v.push_back(make_pair(0, x));
}
cout << dp[n] << '\n';