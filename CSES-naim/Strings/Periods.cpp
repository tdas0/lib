/*
generate the whole string by repeating the prefix.
The last repetition may be partial
*/
vector<int> z = z_function(s);
for(int j=0;j<n;j++){
    if(z[j] == n - j)res.pb(j);
}
res.pb(n);