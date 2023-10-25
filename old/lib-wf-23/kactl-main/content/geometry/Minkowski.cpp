void reorderPolygon(vector<P>& p){
    int pos = 0;
    for(int i=1;i<sz(p);i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x)){
            pos = i;
        }
    }
    rotate(p.begin(),p.begin()+pos,p.end());
}
vector<P> minkowski(vector<P> p, vector<P> q){
    reorderPolygon(p), reorderPolygon(q);
    p.pb(p[0]),p.pb(p[1]),q.pb(q[0]),q.pb(q[1]);
    vector<P> result;
    int i=0,j=0;
    while(i<sz(p)-2 || j<sz(q)-2){
        result.pb(p[i] + q[j]);
        auto cross = (p[i+1] - p[i]).cross(q[j+1] - q[j]);
        if(cross >= 0)++i;
        if(cross <= 0)++j;
    }
    return result;
}