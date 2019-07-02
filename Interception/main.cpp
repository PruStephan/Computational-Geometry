#include "tests.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <cstddef>

using namespace std;

class Dot {
public:
    double x;
    double y;

    Dot(double x, double y) : x(x), y(y) {
    }

    bool operator<=(Dot a) {
        return x <= a.x && y <= a.y;
    }

    bool operator<(Dot a) {
        return x < a.x || ((x == a.x) && (y < a.y));
    }
};

int LeftTurn(Dot a, Dot b, Dot c)
{
    if((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0)
        return 1;
    if((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0)
        return -1;
    return 0;
}



bool between(double a, double b, double c, double d)
{
    if(a > b)
        swap(a, b);
    if(c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

class Line{
public:
    Dot a;
    Dot b;

    Line(Dot a, Dot b) : a(a), b(b) {}


    bool doIntersect(Line x)
    {
        Dot c = x.a;
        Dot d = x.b;
        return between(a.x, b.x, c.x, d.x) && between(a.y, b.y, c.y, d.y) && LeftTurn(a, b, c) * LeftTurn(a, b, d) <= 0
        && LeftTurn(c, d, a) * LeftTurn(c, d, b) <= 0;
    }

};


int main() {
    int testId;
    cin >> testId;

    vector<double> test = genTest(testId);
    string ans = "";
    for(int i = 0; i < test.size(); i = i + 8)
    {
        Dot a(test[i], test[i+1]);
        Dot b(test[i+2], test[i+3]);
        Dot c(test[i+4], test[i+5]);
        Dot d(test[i+6], test[i+7]);

        Line segment1(a, b);
        Line segment2(c, d);
        if(segment1.doIntersect(segment2))
            ans += "Y";
        else
            ans += "N";

    }

    cout << ans;

    return 0;
}