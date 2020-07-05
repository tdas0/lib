/* https://codeforces.com/blog/entry/77298
 * https://codeforces.com/topic/48043/en3
 * Given a sequence of numbers, make operations of +1 or -1 in the elements (both with cost 1)
 * So that it becames not decreasing
 * O(NlogN)
*/
// https://codeforces.com/contest/713/problem/C
rep(i,0,n)a[i]-=i;  
  
priority_queue<ll> pq;
pq.push(a[0]);
rep(i,1,n){
   pq.push(a[i]);
    
   if(pq.top() > a[i]){
      ans+=pq.top() - a[i];
      pq.pop();
      pq.push(a[i]);
   }
}

// Make sequence so that a[i+1] - a[i] >= d
// https://codeforces.com/gym/102576/problem/C

rep(i,0,n)a[i]-=1LL*i*d;  // reduce to the same problem
  
priority_queue<ll> pq;
pq.push(a[0]);
rep(i,1,n){
   pq.push(a[i]);
    
   if(pq.top() > a[i]){
      ans+=pq.top() - a[i];
      pq.pop();
      pq.push(a[i]);
   }
}
