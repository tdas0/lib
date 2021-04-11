// Lydon para minimal rotation - cp algo
string minimal_rotation () {
    s += s;
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n/2) {
        ans = i;
        int j = i+1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] == s[j]) k++;
            else k = i;
            j++;
        }
 
        while (i <= k) i += j-k;
    }
    return s.substr(ans, n/2);
}
