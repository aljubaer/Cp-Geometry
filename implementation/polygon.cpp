#include "line.cpp"

class Polygon {
public:
    int size;
    vector <Point> pts;
    Polygon(vector<Point>& _pts){
        size = pts.size();
        for (Point p : _pts)
            pts.push_back(p);
    }
    double getArea(){
        dl res = 0.0;
        for (int i = 0; i < size-1; i++)
            res += (double)((pts[i].x*pts[i+1].y) - (pts[i+1].x*pts[i].y));
        return fabs(res) / 2.0;
    }
    ll latice_point(){
        ll cnt = 0;
        for (int i = 0; i < size-1; i++){
            int x = (int)(p[i+1].x-p[i].x), y = (int)(p[i+1].y-p[i].y);
            cnt += __gcd(abs(x), abs(y));
        }
        return cnt;
    }
}
