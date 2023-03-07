/*
There is a heap of n coins and two players who move alternately.
On each move, a player chooses a heap and divides into two
nonempty heaps that have a different number of coins.
The player who makes the last move wins the game.
Your task is to find out who wins if both players play optimally.
*/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 5e3;
int nim[MAXN];
 
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int maxnim = 1;
    for (int i = 3; i < MAXN; ++i) {
        vector<int> used(maxnim + 1, 0);
        for (int j = 1; j * 2 < i; ++j) {
            used[nim[j] ^ nim[i - j]] = 1;
        }
        for (int j = 0; j <= maxnim; ++j) {
            if (!used[j]) {
                nim[i] = j;
                break;
            }
        }
        if (nim[i] == maxnim) maxnim *= 2;
    }
    int tst;
    cin >> tst;
    while (tst--) {
        int n;
        cin >> n;
        if (n >= MAXN || nim[n] != 0) {
            cout << "first\n";
        } else {
            cout << "second\n";
        }
    }
    return 0;
}