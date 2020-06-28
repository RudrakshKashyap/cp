https://codeforces.com/blog/entry/48868
https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html

template <class F>
struct Point
{
    F x, y;
    Point() : x(0), y(0) {}
    Point(F x,F y) : x(x), y(y) {}
    bool operator<(const Point &p) const {
        return make_pair(x,y)<make_pair(p.x,p.y);
    }
};

template <class F> using Polygon = vector<Point<F>>;
inline int prev(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int next(int i, int n) { return i == n-1 ? 0 : i+1; }

template <class F>
F area(const Polygon<F>& poly)
{
    int n = static_cast<int>(poly.size());
    F area = F(0);
    for (int i = 0; i < n; ++i)
        area += poly[i].x * (poly[next(i, n)].y - poly[prev(i, n)].y);
    return abs(area)/2; // area can be -ve depending on the orientation
}
//Oriented means that it's positive if polygon vertices are listed in counter-clockwise (ccw) order and negative otherwise.

// template <class F>
// bool cw(Point<F> a, Point<F> b, Poi  nt<F> c) {
//     return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
// }

template <class F>
bool ccw(Point<F> a, Point<F> b, Point<F> c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0; // use >= if you dont wanna include colinear points
}

template <class F>
Polygon<F> convexHull(Polygon<F> points)
{
    sort(begin(points), end(points));
    Polygon<F> hull;
    hull.reserve(points.size() + 1);
    for (int phase = 0; phase < 2; ++phase)
    {
        auto start = hull.size();
        for (auto& point : points)
        {
            while(hull.size() >= start+2
                && ccw(hull[hull.size()-2], hull.back(),point))
            hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(begin(points), end(points));
    }
    if (hull.size() == 2 && (hull[0].x == hull[1].x) && (hull[0].y == hull[1].y)) hull.pop_back();
    return hull; //return clockwise hull
    return reverse(all(hull)); //return ccw hull
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    Polygon<int> p;
    repa(i,1,5)
    {
        repa(j,1,5)
        {
            p.eb(i,j);
        }
    }
    p=convexHull(p);
    rep(i,SZ(p))
    {
        cout<<p[i].x<<' '<<p[i].y<<'\n';
    }
    cout<<area(p)<<'\n';

    return 0;
}

//point inside polygon in O(n)
 bool PIP(point p)
    {
        int n=(int)vertices.size();
        bool ans=true;
        for(int i=0; i<n; i++)
            ans&=ccw(vertices[i], vertices[(i+1)%n], p);
        return ans;
    }



//O(logn)--https://www.youtube.com/watch?v=aoxOPx2BIHE
//another nice approach is in that codeforces blog
long long cross_product(Point<ll> a, Point<ll> b){
    return a.x*b.y-b.x*a.y;
}

long long sq_dist(Point<ll> a, Point<ll> b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

// remove '=' if you consider a point on the edge outside
bool is_inside(Point<ll> p, Polygon<ll>& points){
    Point<ll> p1 = {points[points.size()-1].x-points[0].x, points[points.size()-1].y-points[0].y};
    Point<ll> p2 = {points[1].x-points[0].x, points[1].y-points[0].y};
    Point<ll> pq = {p.x-points[0].x, p.y-points[0].y};

    if(!(cross_product(p1, pq)<=0 && cross_product(p2,pq)>=0)) return false;

    int l = 0, r = points.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        Point<ll> cur = {points[mid].x-points[0].x, points[mid].y-points[0].y};
        if (cross_product(cur, pq)<0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    int f=points.size()-1;
    if(l == f){
        return sq_dist(points[0], {p.x,p.y}) <= sq_dist(points[0], points[l]); //lie on the last edge
    }else{
        Point<ll> l_l1 = {points[l+1].x-points[l].x, points[l+1].y-points[l].y};
        Point<ll> lq = {p.x-points[l].x, p.y-points[l].y};
        return (cross_product(l_l1,lq) >=0);
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin>>q;
    Polygon<ll> poly; //assuming poly is ccw
    while(q--)
    {

        long long x,y;
        cin>>x>>y;
        cout <<  (is_inside(Point<ll>(x,y), poly) ? "YES\n" : "NO\n");
    }

    return 0;
}
