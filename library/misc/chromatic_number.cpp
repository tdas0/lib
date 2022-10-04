/**
 * Author: ??
 * Date: ??-??-??
 * License: ??
 * Source: own work
 * Description: //compute the chromatic number (P(K)= \sum (-1)^{n - |i|} * ind(i)^k) of a graph
 * Time: O(n*2^N)
 * Status: stress-tested
 */






int ChromaticNumber(const vector<int> &g) {
        int n = g.size();
        if (n == 0) return 0;
        //randomly choose a large prime
        const int modulo = 1077563119;
        int all = 1 << n;
        vector<int> ind(all), s(all);
        for (int i = 0; i < all; i ++) s[i] = ((n - __builtin_popcount(i)) & 1 ? -1 : 1);
        ind[0] = 1;
        for (int i = 1; i < all; i ++) {
                int ctz = __builtin_ctz(i);
                ind[i] = ind[i - (1 << ctz)] + ind[(i - (1 << ctz)) & ~g[ctz]];
                if (ind[i] >= modulo) ind[i] -= modulo;
        }
        for (int k = 1; k < n; k ++) {
                long long sum = 0;
                for (int i = 0; i < all; i ++) {
                        long long cur = ((s[i] * (long long) ind[i]) % modulo);
                        s[i] = cur;
                        sum += cur;
                }
                if (sum % modulo != 0) return k;
        }
        return n;
}
