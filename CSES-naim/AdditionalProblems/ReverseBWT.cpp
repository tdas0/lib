/*
BWT:
1)append the character # to the string 
(we assume that # is lexicographically smaller than all other characters of the string)
2)generate all rotations of the string
3)sort the rotations in increasing order
4)based on this order, construct a new string that contains the last character of each rotation
*/
const int MAXN = 1000100;
 
int cnt[30];
int pre[30];
int L[MAXN];
 
int32_t main(){
    fastio;
    string s;
    cin>>s;  
    int n = s.size();
    for(int i=0;i<n;i++){
        if(s[i]=='#')pre[0]++;
        else{
            pre[s[i]-'a' + 1]++;
        }
    }
    for(int i=0;i<29;i++){
        pre[i+1]+=pre[i];
    }
    for(int i=0;i<n;i++){
        if(s[i]=='#'){
            L[i] = pre[0];
        }else{
            L[i] = pre[s[i]-'a'] + cnt[s[i]-'a'] + 1;
            cnt[s[i]-'a'] ++;
        }
   
    }
    string t = "";
    t+=s[0];
    int cur = L[0]-1;
    while(t.size()<n){
        t+=s[cur];
        cur = L[cur]-1;
       
    }
    reverse(all(t));
    for(int i=1;i<n;i++){
        cout<<t[i];
    }
    cout<<endl;
    // Math -> gcd it all
    //did you check N=1? Did you mix up N,M?
}