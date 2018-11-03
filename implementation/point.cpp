#include "includes.cpp"
enum { LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION } ;

class Point{
public:
    ll x, y;
    Point(){x = y = 0;}
    Point(ll X, ll Y) : x(X), y(Y){}
    void make_point(ll X, ll Y) { x = X; y = Y; }
    Point operator+ (Point &p)const { return Point(x + p.x, y + p.y); }
    Point operator- (Point &p)const { return Point(x - p.x, y - p.y); }
    Point operator* (ll s)const { return Point(x * s, y * s); }
    bool operator== (Point &p)const { return (x == p.x && y == p.y); }
    bool operator!= (Point &p)const { return (x != p.x || y != p.y); }
    bool operator< (Point &p)const { return ((x < p.x) || ((x == p.x) && (y < p.y))); }
    bool operator> (Point &p)const { return ((x > p.x) || ((x == p.x) && (y > p.y))); }
    ll dot(Point &p)const { return x*p.x + y*p.y; }
    ll length2(){ return (sqr(x) + sqr(y)); }
    double length(){ return sqrt((double)length2()); }
    int orientation (Point &p0, Point &p1);
    int classify(Point &p0, Point &p1);
    //int classify(const Edge &e) const { return classify(e.org, e.dest); }
    double polarAngle();
};

int Point:: orientation (Point &p0, Point &p1){
    Point p2 = *this;
    Point a = p1 - p0;
    Point b = p2 - p0;
    ll area = (a.x * b.y) - (b.x * a.y);
    if (area > 0LL)return 1;
    if (area < 0LL)return -1;
    return 0;
}

int Point:: classify(Point &p0, Point &p1){
    Point p2 = *this;
    Point a = p1 - p0;
    Point b = p2 - p0;
    ll area = a.x * b.y - b.x * b.y;
    if (area > 0LL)return LEFT;
    if (area < 0LL)return RIGHT;
    if ((a.x * b.x < 0) || (a.y * b.y < 0))
        return BEHIND;
    if (a.length() < b.length())
        return BEYOND;
    if (p0 == p2) return ORIGIN;
    if (p1 == p2) return DESTINATION;
    return BETWEEN;
}

double Point:: polarAngle(){
    if (x == 0){
        if (y == 0)return -1.0;
        if (y > 0)return 90.0;
        return 270;
    }
    double theta = atan((double)y / (double)x);
    theta *= 360.0 / (2.0 * PI);
    if (x > 0)
        return ((y >= 0) ? theta : theta + 360 );
    else
        return (180 + theta);
}

class PointFp {
public:
    double x, y;
    PointFp(){x = y = 0;}
    PointFp(double X, double Y) : x(X), y(Y){}
    PointFp(ll X, ll Y) : x(X), y(Y){}
    void make_point(double X, double Y) { x = X; y = Y; }
    PointFp operator+ (PointFp &p)const { return PointFp(x + p.x, y + p.y); }
    PointFp operator- (PointFp &p)const { return PointFp(x - p.x, y - p.y); }
    PointFp operator* (double s)const { return PointFp(x * s, y * s); }
    bool operator== (PointFp &p)const { return (fabs(x - p.x) < EPS && fabs(y - p.y) < EPS); }
    bool operator!= (PointFp &p)const { return (fabs(x - p.x) > EPS || fabs(y - p.y) < EPS); }
    bool operator< (PointFp &p)const { return ((p.x - x > EPS) || ((fabs(x - p.x)) < EPS && (p.y - y > EPS))); }
    bool operator> (PointFp &p)const { return ((x - p.x > EPS) || ((fabs(x - p.x)) < EPS && (y - p.y > EPS))); }
    double dot(PointFp &p)const { return x*p.x + y*p.y; }
    double length2(){ return (sqr(x) + sqr(y)); }
    double length(){ return sqrt((double)length2()); }
    int orientation (PointFp &p0, PointFp &p1);
    int classify(PointFp &p0, PointFp &p1);
    int classify(Point p0, Point p1);
    //int classify(const Edge &e) const { return classify(e.org, e.dest); }
    double polarAngle();
};

int PointFp:: orientation (PointFp &p0, PointFp &p1){
    PointFp p2 = *this;
    PointFp a = p1 - p0;
    PointFp b = p2 - p0;
    double area = (a.x * b.y) - (b.x * a.y);
    return fsign(area);
}

int PointFp:: classify(PointFp &p0, PointFp &p1){
    PointFp p2 = *this;
    PointFp a = p1 - p0;
    PointFp b = p2 - p0;
    double area = a.x * b.y - b.x * b.y;
    if (area - EPS > 0.0)return LEFT;
    if (area + EPS < 0.0)return RIGHT;
    if ((a.x * b.x + EPS < 0) || (a.y * b.y + EPS < 0))
        return BEHIND;
    if (b.length() - a.length() > EPS)
        return BEYOND;
    if (p0 == p2) return ORIGIN;
    if (p1 == p2) return DESTINATION;
    return BETWEEN;
}

int PointFp:: classify(Point p0, Point p1){
    PointFp pf1(p0.x, p0.y);
    PointFp pf2(p1.x, p1.y);
    return this->classify(pf1, pf2);
}

double PointFp:: polarAngle(){
    if (x == 0.0){
        if (y == 0.0)return -1.0;
        if (y > 0.0)return 90.0;
        return 270;
    }
    double theta = atan((double)y / (double)x);
    theta *= 360.0 / (2.0 * PI);
    if (x > 0.0)
        return ((y >= 0.0) ? theta : theta + 360 );
    else
        return (180.0 + theta);
}

class Vector {
public:
    double x, y;
    Vector(){x = y = 0.0;}
    Vector(double X, double Y):x(X), y(Y){}
    Vector(Point a, Point b){
        x = (double)b.x - a.x;
        y = (double)b.y - a.y;
    }
    Vector(PointFp a, PointFp b){
        x = b.x - a.x;
        y = b.y - a.y;
    }
    double dot( Vector &b ){
        return x*b.x + y*b.y;
    }
    double normSq(){
        return x*x + y*y;
    }
};

// angle <aob
double angle(Point a, Point o, Point b){
    Vector oa(o, a);
    Vector ob(o, b);
    return radToDegree(acos(oa.dot(ob) / sqrt(oa.normSq() * ob.normSq())));
}

// Test algo here ..............

// int main() {
//
//
//     return 0;
// }
