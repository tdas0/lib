/**
 * Author: ?
 * Date: 2020-03-22
 * Description: Passar por todas as submasks de uma masks. 
 * Se fizer esse processo para cada mask possível O(3^n)
 * Time: O(3^n) no total, porem O(2^n) para cada mask individual
 * Status: ?
 */
 
 // O(3^n)
 for (int m=0; m<(1<<n); ++m){
    for (int s=m; s; s=(s-1)&m){
      //S = submask de m
  }
 }
 
 //percorrer todas as submasks de M (tested)
 int s = m;
while (s > 0) {
 //... you can use s ...
 s = (s-1) & m;
}

 //percorrer todas as submasks de M (not tested)
 for (int s=m; s; s=(s-1)&m){
     //... you can use s ...
 }
