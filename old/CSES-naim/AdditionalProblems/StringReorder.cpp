// menor permutacao lexic. sem ter adj igual
#include <bits/stdc++.h>
long long cnt[27];
using namespace std;
int main()
{
        long long n,i,ii,mx,ok,lst=26;
        string s;
        cin>>s;
        n=s.length();
        for(i=0;i<n;i++)
        {
                cnt[s[i]-'A']++;
        }
        for(i=0;i<26;i++)
        {
                if(cnt[i]>(n+1)/2)
                {
                        printf("-1\n");
                        return 0;
                }
        }
        for(i=0;i<n;i++)
        {
                for(ii=0;ii<26;ii++)
                {
                        if(cnt[ii]>0&&ii!=lst)
                        {
                                ok=ii;
                                break;
                        }
                }
                mx=0;
                for(ii=0;ii<26;ii++)
                {
                        if(ii!=ok&&ii!=lst&&cnt[ii]>cnt[mx])
                        {
                                mx=ii;
                        }
                }
                if(cnt[mx]>(n-i)/2)
                {
                        printf("%c",(char)(mx+'A'));
                        cnt[mx]--;
                        lst=mx;
                }
                else
                {
                        printf("%c",(char)(ok+'A'));
                        cnt[ok]--;
                        lst=ok;
                }
        }
}