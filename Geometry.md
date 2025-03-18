
## Point structure and operations
- Codeforces Blog -> [Geometry: 2D points and lines [Tutorial]](https://codeforces.com/blog/entry/48122)
- Dot product: dot product sign indicates whether two vectors point in about the same direction.
- 2D cross product: 2D cross product indicates whether the shortest turn from a to b is in the counter-clockwise direction.
```cpp

template <class F>
struct Point
{
    F x, y;
    Point() : x(0), y(0) {}
    Point(const F &x, const F &y) : x(x), y(y) {}

    void swap(Point &other)
    {
        using std::swap;
        swap(x, other.x);
        swap(y, other.y);
    }

    // The explicit keyword ensures that the conversion must be explicitly 
    // requested using static_cast. 
    template <class F1>
    explicit operator Point<F1>() const {
        return Point<F1>(static_cast<F1>(x), static_cast<F1>(y));
    }

    template <class F1>
    Point &operator = (const Point<F1> &other)
    {
        x = other.x;
        y = other.y;
        return *this;   //allows Assignment Chains like A = B = C
    }
    template <class F1>
    Point &operator += (const Point<F1> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    template <class F1>
    Point &operator -= (const Point<F1> &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    template <class F1>
    Point &operator *= (const F1 &factor)
    {
        x *= factor;
        y *= factor;
        return *this;
    }
    template <class F1>
    Point &operator /= (const F1 &factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }
};


template <class F>
istream &operator>>(istream &is, Point<F> &point) {
    return is >> point.x >> point.y;
}

template <class F>
ostream &operator<<(ostream &os, const Point<F> &point) {
    return os << point.x << ' ' << point.y;
}

template <class F>
inline Point<F> makePoint(const F &x, const F &y) { return Point<F>(x, y); }

template <class F>
void swap(Point<F> &lhs, Point<F> &rhs) { lhs.swap(rhs); }

#define FUNC1(name, arg, expr) \
    template <class F>         \
    inline auto name(const arg) -> decltype(expr) { return expr; }

#define FUNC2(name, arg1, arg2, expr) \
    template <class F1, class F2>     \
    inline auto name(const arg1, const arg2) -> decltype(expr) { return expr; }

#define FUNC3(name, arg1, arg2, arg3, expr) \
    template <class F1, class F2, class F3> \
    inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) { return expr; }

FUNC1(operator-, Point<F> &point, makePoint(-point.x, -point.y))
FUNC2(operator+, Point<F1> &lhs, Point<F2> &rhs, makePoint(lhs.x + rhs.x, lhs.y + rhs.y))
FUNC2(operator-, Point<F1> &lhs, Point<F2> &rhs, makePoint(lhs.x - rhs.x, lhs.y - rhs.y))
FUNC2(operator*, F1 &factor, Point<F2> &rhs, makePoint(factor *rhs.x, factor *rhs.y))
FUNC2(operator*, Point<F1> &lhs, F2 &factor, makePoint(lhs.x *factor, lhs.y *factor))
FUNC2(operator/, Point<F1> &lhs, F2 &factor, makePoint(lhs.x / factor, lhs.y / factor))

// Dot & Cross Products
FUNC2(operator*, Point<F1> &lhs, Point<F2> &rhs, lhs.x * rhs.x + lhs.y * rhs.y) //|a||b|cos0
FUNC2(operator^, Point<F1> &lhs, Point<F2> &rhs, lhs.x * rhs.y - lhs.y * rhs.x) //|a||b|sin0 -> area of parallelogram

// > 0 if rhs <- lhs counter-clockwise, 0 if collinear, < 0 if clockwise.
FUNC2(ccw, Point<F1> &lhs, Point<F2> &rhs, lhs ^ rhs)
FUNC3(ccw, Point<F1> &lhs, Point<F2> &rhs, Point<F3> &origin, ccw(lhs - origin, rhs - origin))

FUNC2(operator==, Point<F1> &lhs, Point<F2> &rhs, lhs.x == rhs.x && lhs.y == rhs.y)
FUNC2(operator!=, Point<F1> &lhs, Point<F2> &rhs, !(lhs == rhs))

//Sorting Based on Y coordinate first
FUNC2(operator<, Point<F1> &lhs, Point<F2> &rhs,
      lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x))
FUNC2(operator>, Point<F1> &lhs, Point<F2> &rhs, rhs < lhs)
FUNC2(operator<=, Point<F1> &lhs, Point<F2> &rhs, !(lhs > rhs))
FUNC2(operator>=, Point<F1> &lhs, Point<F2> &rhs, !(lhs < rhs))

// Angles and rotations (counter-clockwise).
FUNC1(angle, Point<F> &point, atan2(point.y, point.x))  //[-π, π](in radians)
FUNC2(angle, Point<F1> &lhs, Point<F2> &rhs, atan2(lhs ^ rhs, lhs * rhs))
FUNC3(angle, Point<F1> &lhs, Point<F2> &rhs, Point<F3> &origin,
      angle(lhs - origin, rhs - origin))
FUNC3(rotate, Point<F1> &point, F2 &angleSin, F3 &angleCos,
      makePoint(angleCos * point.x - angleSin * point.y,
                angleSin * point.x + angleCos * point.y))
FUNC2(rotate, Point<F1> &point, F2 &angle, rotate(point, sin(angle), cos(angle)))
FUNC3(rotate, Point<F1> &point, F2 &angle, Point<F3> &origin,
      origin + rotate(point - origin, angle))
FUNC1(perp, Point<F> &point, makePoint(-point.y, point.x))  //rotating by π / 2.

// Distances.
FUNC1(abs, Point<F> &point, point * point)
FUNC1(norm, Point<F> &point, sqrt(abs(point)))
FUNC2(dist, Point<F1> &lhs, Point<F2> &rhs, norm(lhs - rhs))
FUNC2(dist2, Point<F1> &lhs, Point<F2> &rhs, abs(lhs - rhs))
FUNC2(bisector, Point<F1> &lhs, Point<F2> &rhs, lhs * norm(rhs) + rhs * norm(lhs))

#undef FUNC1
#undef FUNC2
#undef FUNC3

```
## Polygon
- Codeforces Blog -> [Geometry: Polygon algorithms](https://codeforces.com/blog/entry/48868)
- [Errichto YT - CSES Geometry Problem Set](https://www.youtube.com/watch?v=G9QTjWtK_TQ)
- [YT - Graham Scan and Jarvis March for Convex hull](https://www.youtube.com/watch?v=B2AJoQSZf4M)

```cpp
template <class F>
using Polygon = vector<Point<F>>;
inline int prev(int i, int n) { return i == 0 ? n - 1 : i - 1; }
inline int next(int i, int n) { return i == n - 1 ? 0 : i + 1; }
template <class T>
inline int sgn(const T &x) { return (T(0) < x) - (x < T(0)); }
```

### 1. Area: O(N)
This function returns doubled oriented area. Doubled, because for any polygon with integer coordinated the area may be not integer but half-integer. 

Oriented means that it's positive if polygon vertices are listed in counter-clockwise (ccw) order and negative otherwise.

```cpp
template <class F>
F area(const Polygon<F> &poly)
{
    int n = static_cast<int>(poly.size());
    F area = F(0);
    for (int i = 0; i < n; ++i)
        area += poly[i].x * (poly[next(i, n)].y - poly[prev(i, n)].y);
    return area; //    / 2.0
}
```
### 2. Convex hull: O(NlogN)

```cpp
template <class F>
Polygon<F> convexHull(Polygon<F> points)
{
    //right and left chains (because we sorted by Y first) / lower and then upper if sorted by x
    sort(begin(points), end(points));
    Polygon<F> hull;
    hull.reserve(points.size() + 1);
    for (int phase = 0; phase < 2; ++phase)
    {
        auto start = hull.size();
        for (auto &point : points)
        {
            while (hull.size() >= start + 2 &&
                   ccw(point, hull.back(), hull[hull.size() - 2]) >= 0)
                hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();    //pop the topmost point
        reverse(begin(points), end(points));
    }
    //case when all the points coincide
    if (hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
    return hull;
}
```
