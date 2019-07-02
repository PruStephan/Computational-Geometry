#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double ans;

class Dot{
public:
    long long x;
    long long y;

    Dot(long long x, long long y) : x(x), y(y) {}
    Dot() : x(0), y(0) {};
    bool operator==(Dot a) {
        return x  == a.x && a.y == y;
    }

    bool operator<(const Dot &a) const {
        return x < a.x || (a.x == x && y < a.y);
    }

    void print() {
        cout << x << " " << y << endl;
    }
};

double Distance(Dot a, Dot b) {
    return sqrt((a.x - b. x) * (a.x - b.x) + (a.y - b. y) * (a.y - b.y));
}

class Line{
    Dot start;
    Dot end;

    Line(Dot a, Dot b) : start(a), end(b) {}

    double Angle(const Line &line) {
        double cur_x = end.x - start.x;
        double cur_y = end.y - start.y;

        double line_x = line.end.x - line.start.x;
        double line_y = line.end.y - line.start.y;

        double cur = Distance(start, end);
        double line_d = Distance(line.start, line.end);

        return (cur_x * line_x + cur_y * line_y) / (cur * line_d);
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


pair<vector<Dot>, vector<Dot>> ConvexHull(vector<Dot> &dots) {
    sort(dots.begin(), dots.end());
    Dot a = dots[0];
    Dot b = dots[dots.size() - 1];
    ans = Distance(a, b);
    vector<Dot> up, down;
    up.push_back(a);
    down.push_back(a);
    for(size_t i = 0; i < dots.size(); i++) {
        if (i==dots.size()-1 || LeftTurn (a, dots[i], b) == -1) {
            while (up.size()>=2 && LeftTurn(up[up.size()-2], up[up.size()-1], dots[i]) >= 0)
                up.pop_back();
            up.push_back (dots[i]);
        }
        if (i==dots.size()-1 || LeftTurn (a, dots[i], b) == 1) {
            while (down.size()>=2 && LeftTurn(down[down.size()-2], down[down.size()-1], dots[i]) <= 0)
                down.pop_back();
            down.push_back (dots[i]);
        }
    }


    reverse(down.begin(), down.end());

    return make_pair(up, down);
}

int ConvexHull2(vector<Dot> &dots) {
    if(dots.size() <= 3)
        return -1;

    vector<Dot> hull(2 * dots.size());
    sort(dots.begin(), dots.end());

    int num = 0;

    int k = 0;
    for(int i = 0; i < dots.size(); i++)
    {
        while(k >= 2 && LeftTurn(hull[k - 2], hull[k - 1], dots[i]) <= 0)
            k--;
        hull[k++] = dots[i];
    }

    num = k;

    for(int i = dots.size() - 1, t = k + 1; i > 0; --i) {
        while(k >= t && LeftTurn(hull[k - 2], hull[k - 1], dots[i - 1]) <= 0)
            k--;
        hull[k++] = dots[i - 1];
    }
    hull.resize(k - 1);
    dots = hull;
    return num;
}


double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    size_t n;
    cin >> n;
    vector<Dot> dots;
    for(int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        dots.push_back(Dot(a, b));
    }

    pair<vector<Dot>, vector<Dot>> hulls = ConvexHull(dots);

    vector<Dot> up = hulls.first;
    vector<Dot> down = hulls.second;

    n = dots.size();


    up.insert(up.begin(), down[down.size() - 2]);
    down.insert(down.begin(), up[up.size() - 2]);

    size_t i = up.size() - 1, j = down.size() - 1;
    while(i != 1 && j != 1) {
        ans = max(ans, Distance(up[i], down[j]));
        ans = max(ans, Distance(up[i], down[j - 1]));
        ans = max(ans, Distance(up[i - 1], down[j]));
        ans = max(ans, Distance(up[i - 1], down[j - 1]));
        if (LeftTurn(Dot(down[j].x + (up[(i - 1)].x - up[i].x), down[j].y + (up[(i - 1)].y - up[i].y)), down[j], down[(j - 1)]) > 0)
            i--;
        else
            j--;
    }
    ans = max(ans, Distance(up[i], down[j]));
    ans = max(ans, Distance(up[i], down[j - 1]));
    ans = max(ans, Distance(up[i - 1], down[j]));
    ans = max(ans, Distance(up[i - 1], down[j - 1]));

    cout.precision(15);
    cout << ans;

    return 0;
}