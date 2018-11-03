#include "point.cpp"

class Line{
public:
    ll a, b, c;
    Point p1, p2;
    Line(){a = b = c = 0;}
    Line(Point _p1, Point _p2){
        p1 = _p1;
        p2 = _p2;
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -((p1.y*(p1.x-p2.x))+(p1.x*(p2.y-p1.y)));
    }
    bool operator|| (Line &l)const{ return a == l.a && b == l.b; }
    bool operator== (Line &l)const{ return (*this || l) && c == l.c; }
    pair<bool, PointFp> intersect(Line &l);
    pair<bool, PointFp> intersect(Point p1, Point p2);
    bool intersectByCreamers(Line l, Point &p);
};

bool Line:: intersectByCreamers(Line l, Point &p){
        if (*this || l)return false;
        double determinant = (double)a*l.b - b*l.a;
        if (determinant == 0.0 || determinant + EPS == 0.0 || determinant - EPS == 0.0){
            return false;
        }
        double c1 = -c, c2 = -l.c;
        p.x = (double)((double)c1*l.b - b*c2)/determinant;
        p.y = (double)((double)a*c2 - c1*l.a)/determinant;
        //cout << p.x << ' ' << p.y << '\n';
    }

pair<bool, PointFp> Line:: intersect(Point lp1, Point lp2){
    Line l(lp1, lp2);
    return intersect(l);
}

pair<bool, PointFp> Line:: intersect(Line &l){
    PointFp p(INF, INF);
    ll dx, dy, m1, m2;
    dl c1, c2;
    dx = p1.x - p2.x;
    dy = p1.y - p2.y;
    m1 = dx == 0 ? INF : dy / dx;
    c1 = p1.y - m1 * p1.x;
    dx = l.p1.x - l.p2.x;
    dy = l.p1.y - l.p2.y;
    m2 = dx == 0 ? INF : dy / dx;
    c2 = l.p1.y - m2 * l.p1.x;
    if (m1 == m2){
        return make_pair(false, p);
    }
    if (m1 == INF) p.x = 0;
    else p.x = (double)(c2 - c1) / (m1 - m2);
    p.y = m1 * p.x + c1;
    return make_pair(true, p);;
}

class Segment : public Line {
public:
    Segment(Point p1, Point p2): Line(p1, p2){}
    pair <bool, PointFp> intersectSegment(Point lp1, Point lp2){
        PointFp p(INF, INF);
        pair <bool, PointFp> inPP = intersect(lp1, lp2);
        if (!inPP.first){
            return make_pair(false, p);
        }
        cout << inPP.second.x << '\n';
        p = inPP.second;
        int c = p.classify(p1, p2);
        int d = p.classify(lp1, lp2);
        if ( (c == BETWEEN || c == ORIGIN || c == DESTINATION)
            && (d == BETWEEN || d == ORIGIN || d == DESTINATION)){
            return make_pair(true, p);
        }
        return make_pair(false, p);
    }
    pair <bool, PointFp> intersectSegment(Segment s){
        return intersect(s.p1, s.p2);
    }
};

class Ray {
public:
    Point src, dest;
    double slop;
    bool operator< (Ray r){
        return (slop < r.slop);
    }
    Ray(Point s, Point d){
        src = s, dest = d;
        double dy = (double)(dest.y-src.y);
        double dx = (double)(dest.x-src.x);
        if (fabs(dx) < EPS){
            if (dy - EPS > 0)slop = 90;
            else slop = 270;
        }
        else slop = radToDegree(atan((double)dy / dx));
        if (dx >= 0 && dy >= 0)slop = slop;
        else if (dx >= 0 && dy < 0)slop += 360.0;
        else slop += 180.0;
        if (slop > 360.0)slop -= 360.0;
    }

};

int main() {
    Point p1(-1, 0), q1(1, 0);
    Point p2(0, -1), q2(0, 0);
    Segment s1( p1, q1 );
    Segment s2( p2, q2 );
    pair <bool, PointFp> p = s1.intersectSegment(s2);
    if (p.first){
        cout << "Found: ";
        cout << fixed;
        cout << setprecision(10) << p.second.x + EPS << " " << p.second.y + EPS << '\n';
    }
}









// end here
