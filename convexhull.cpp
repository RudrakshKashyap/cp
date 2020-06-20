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
    return area;
}

// template <class F>
// bool cw(Point<F> a, Point<F> b, Point<F> c) {
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
    return hull;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    Polygon<int> p;
    repa(i,1,5)
    {
        repa(j,1,5) p.eb(i,j);
    }
    p=convexHull(p);
    rep(i,SZ(p))
    {
        cout<<p[i].x<<' '<<p[i].y<<'\n';
    }

    return 0;
}
