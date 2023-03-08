/*
You would like to write a list of positive integers 1,2,3,
using your computer. However, you can press each key at most n
times during the process.
What is the last number you can write?
*/
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
 
int count(int n) {
    int val = 1;
    for (int i = 0; i < 18; ++i) {
        val *= 10;
    }
    int ans = 0;
    for (int i = 18; i >= 0; --i) {
        int k = n / val;
        ans += k * i * (val / 10);
        if (k >= 2) {
            ans += val;
        } else if (k == 1) {
            ans += (n - val + 1);
        }
        n %= val;
        val /= 10;
    }
    return ans;
}
 
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int l = 0, r = 1e18;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (count(m) <= n) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << "\n";
    return 0;
}