/* Source: https://cp-algorithms.com/string/prefix-function.html
 * Description: Builds automaton on string in O(alpha * |S|)
 * aut[i][c] -> next position if on position 'i' and adding the c-th character 
 * Assumes the first character is 'a', next 'b'...
 * Tested on https://codeforces.com/group/q6XD0oW97M/contest/274944/problem/B
 * Tested on 104003/problem/K
 */
 
 // build prefix function
 vector<int> prefix_function(string s) {
    int n = sz(s);
    vector<int> pi(n);
    rep(i,1,n) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vi pi;
vector<vi> aut;
void compute_automaton(string s,int alpha = 26) {
    s += '#'; 
    int n = sz(s);
     pi = prefix_function(s);
    aut.assign(n+1, vector<int>(alpha));
    rep(i,0,n){
        rep(c,0,alpha){
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
