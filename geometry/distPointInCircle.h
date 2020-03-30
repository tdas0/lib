/**
 * Author: Naim
 * Date: 2020-03-30
 * Source:Math
 * Description:
 * dados a e b no circulo acha a distancia deles;
 * Centro eh C e raio R;
 * Usa Lei dos Cossenos Para calcular o angulo
 * Assume que a e b estão no circulo
 * Status: tested 
 */
 
 #include "Point.h"
 typedef Point<double> P;
 
 double distCircle(P a,P b,P C,double R){

    if((a-b).dist()<EPS)return (a-b).dist();
    double d = (a-b).dist();
    double ang = acos((d*d - 2.0*R*R)/(-2.0*R*R));
    if(ang<0)ang+=2*PI;
    
    return R*ang;
}
