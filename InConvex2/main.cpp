#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Dot {
public:
    long long x, y;
    Dot(long long x, long long y) : x(x), y(y){}
    Dot() : x(0), y(0) {}

    bool operator<(const Dot &a) const {
        return (x < a.x) || ((x == a.x) && (y < a.y));
    }

    bool operator==(const Dot &a) const {
        return a.x == x && a.y == y;
    }
};


int LeftTurn(Dot a, Dot b, Dot c) {
    double ans = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if(ans == 0)
        return 0;
    if(ans > 0)
        return 1;
    return -1;
}


long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

bool between(long long a, long long b, long long c, long long d)
{
    if(a > b)
        swap(a, b);
    if(c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool between1(Dot q, Dot a, Dot b) {
    return abs(sqrt((a.x - q.x) * (a.x - q.x) + (a.y - q.y) * (a.y - q.y)) + sqrt((b.x - q.x) * (b.x - q.x) + (b.y - q.y) * (b.y - q.y)) - sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y))) < 0.0000001;
}


class Line {
public:
    Dot a;
    Dot b;

    Line(Dot a, Dot b) : a(a), b(b) {}

    bool do_intercept(const Line &q) const {
        Dot c = q.a;
        Dot d = q.b;
        return between(a.x, b.x, c.x, d.x) && between(a.y, b.y, c.y, d.y) && LeftTurn(a, b, c) * LeftTurn(a, b, d) <= 0
               && LeftTurn(c, d, a) * LeftTurn(c, d, b) <= 0;
    }
};

string Check(vector<Dot> &dots, int turn, Dot p, Dot q) {
    int l = -1, r = dots.size();
    while(r - l  > 1){
        int m = (l + r) / 2;
        if(turn * LeftTurn(p, dots[m], q) <= 0)
            r = m;
        else
            l = m;
    }
    if(l == -1)
    {
        l++, r++;
    }
    if(r == dots.size())
    {
        l--, r--;
    }

    int lt = LeftTurn(dots[l], dots[r], q);
    if(!(turn * LeftTurn(p, dots[l], q) >= 0 && turn * lt >= 0 && turn * LeftTurn(p, dots[r], q) <= 0))
        return "OUTSIDE";
    if(lt == 0 && Line(dots[l], dots[r]).do_intercept(Line(p, q)))
        return "BORDER";
    else{
        if(turn * lt <= 0)
            return "OUTSIDE";
        else
            return "INSIDE";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<Dot> dots;
    for(int i = 0; i < n; i++)
    {
        long long x, y;
        cin >> x >> y;
        dots.push_back(Dot(x, y));
    }
    int k;
    cin >> k;

    int turn = LeftTurn(dots[0], dots[1], dots[2]);
    Dot p0, p1, pn_1;
    p0 = dots[0];
    p1 = dots[1];
    pn_1 = dots[n - 1];

    dots = vector<Dot>(dots.begin()+1, dots.end());




    for(int i = 0; i < k; i++) {
        long long a, b;
        cin >> a >> b;
        Dot q(a, b);
        if(turn * LeftTurn(p0, p1, q) == -1 || turn * LeftTurn(p0, pn_1, q) == 1)
        {
            cout << "OUTSIDE" << endl;
        }
        else if((LeftTurn(p0, p1, q) == 0 && between1(q, p0, p1)) || (LeftTurn(p0, pn_1, q) == 0 && between1(q, p0, pn_1)))
        {
            cout << "BORDER" << endl;
        }
        else
        {
            cout << Check(dots, turn, p0, q) << endl;
        }

    }


    return 0;
}