#include "point.cpp"

typedef vector <Point> Polygon;

Point pivot;
// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b) {
    int order = pivot.orientation(b, a);
    if (order == 0)
        return pivot.distance2(a) < pivot.distance2(b);
    return (order == -1);
}

class ConvexHull {
private:
    int size;
    stack <Point> hull;
    Polygon input, output;

    static bool NORMAL_ORDER(Point a, Point b) {
        if (a.y != b.y)
            return a.y < b.y;
        return a.x < b.x;
    }

    void solveByGrahum(Polygon &p) {
        size = p.size();
        if (size < 3){
            solved = false;
            return;
        }
        // find the point having the least y coordinate (pivot),
        // ties are broken in favor of lower x coordinate
        int leastY = 0;
        for (int i = 1; i < size; i++)
            if (p[i] < p[leastY])
                leastY = i;

        // swap the pivot with the first point
        Point temp = p[0];
        p[0] = p[leastY];
        p[leastY] = temp;

        // sort the remaining point according to polar order about the pivot
        pivot = p[0];
        sort(p.begin(), p.end(), NORMAL_ORDER);
        sort(++p.begin(), p.end(), POLAR_ORDER);
        hull.push(p[0]);
        hull.push(p[0]);
        hull.push(p[0]);
        for (int i = 1; i < size; i++) {
            Point top = hull.top();
            hull.pop();
            while (!hull.empty() && hull.top().orientation(p[i], top) != -1){
                top = hull.top();
                hull.pop();
            }
            hull.push(top);
            hull.push(p[i]);
        }
    }

public:
    bool solved = true;
    ConvexHull(Polygon &p){
        for (Point ip: p){
            input.push_back(ip);
        }
    }
    bool isSolvable(){ solveByGrahum(input); return solved; }
    Polygon getSolution(){
        while (!hull.empty()){
            output.push_back(hull.top());
            hull.pop();
        }
        reverse(output.begin(), output.end());
        return output;
    }
};


int main() {
    //Point points[] = {{0, 0}, {1, 1}, {2, 2}, {3, -1}, {3, -3}, {0, -3}, {0, -2}, {0, -1}};
    Polygon p;
    p.push_back(Point{0, 0});
    p.push_back(Point{1, 1});
    p.push_back(Point{2, 2});
    p.push_back(Point{3, -1});
    p.push_back(Point{3, -3});
    p.push_back(Point{0, -3});
    p.push_back(Point{0, -2});
    p.push_back(Point{0, -1});

    ConvexHull ch(p);

    if (ch.isSolvable()){
        Polygon ans = ch.getSolution();
        for (Point p: ans){
            cout << p.x << ' ' << p.y << '\n';
        }
    }
}
