#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Dot{
public:
    double x, y;

    bool operator<(const Dot &a) const {
        return x < a.x || (x == a.x && y < a.y);
    }

    void operator=(const Dot &a) {
        x = a.x;
        y = a.y;
    }

    bool operator==(const Dot &a)  const {
        return a.x == x && a.y == y;
    }

    Dot(double x, double y) : x(x), y(y) {}
    Dot() : x(0), y(0) {}
};

bool between(Dot q, Dot a, Dot b) {
    double dist_qa = sqrt((a.x - q.x) * (a.x - q.x) + (a.y - q.y) * (a.y - q.y));
    double dist_qb = sqrt((b.x - q.x) * (b.x - q.x) + (b.y - q.y) * (b.y - q.y));
    double dist_ab = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

    return abs(dist_qa + dist_qb - dist_ab) < 0.0000001;

}

int LeftTurn(Dot a, Dot b, Dot c) {
    if ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0)
        return 1;
    if ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0)
        return -1;
    return 0;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}


class Line {
public:
    Dot start;
    Dot end;

    Line(Dot a, Dot b) {
        start = a;
        end = b;
    }

    bool do_intercept(Line q) {
        double k1, k2, b1, b2;
        b1 = end.y;
        if(q.start.x == q.end.x)
        {
            return between({q.start.x, end.y}, start, end) && between({q.start.x, end.y}, q.start, q.end);
        }
        k2 =(q.end.y - q.start.y) / (q.end.x - q.start.x);
        b2 = -q.start.x * (q.end.y - q.start.y) / (q.end.x - q.start.x) + q.start.y;
        Dot inter = {(b1 - b2)/k2, b1};
        return between(inter, start, end) && between(inter, q.start, q.end);
    }
};

bool CheckInside(vector<Dot> dots, Dot q) {
    int ans = 0;
    char first(97);
    char second(98);
    for(int i = 0; i < dots.size() - 1; i++, first++, second++) {
        Dot cur = dots[i];
        Dot next = dots[i + 1];
        if(between(q, cur, next))
            return true;
        if(q.y > max(cur.y, next.y) || q.y <= min(cur.y, next.y) || cur.y == next.y)
            continue;
        Dot max_dot = max(cur.y, next.y) == cur.y ? cur : next;
        if(q.x < max_dot.x && q.y == max_dot.y) {
            ans++;
            continue;
        }
        Line q_line = Line(q,Dot(max(cur.x, next.x) + 10, q.y));
        if(q_line.do_intercept(Line(cur, next)))
            ans++;
    }

    return ans % 2 != 0;
}

int main() {

    int n, qx, qy;
    cin >> n >> qx >> qy;
    Dot q(qx, qy);

    vector<Dot> dots;

    for(int i = 0; i < n; i++) {
        Dot a;
        cin >> a.x >> a.y;
        dots.push_back(a);
    }

    dots.push_back(dots[0]);

    if(CheckInside(dots, q))
        cout << "YES";
    else
        cout << "NO";


    return 0;
}