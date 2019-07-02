#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Dot{
public:
    long double x;
    long double y;

    Dot(long double x, long double y) : x(x), y(y) {}
    Dot() = default;

    bool operator<(const Dot &a) const {
        return (x < a.x) || (x == a.x) && (y < a.y);
    }

    bool operator==(const Dot &a) const{
        return a.x == x && a.y == y;
    }

    bool operator!=(const Dot &a) const {
        return !(*this == a);
    }

};

int LeftTurn(Dot a, Dot b, Dot c) {
    long double ans = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if(ans == 0)
        return 0;
    if(ans > 0)
        return 1;
    return -1;
}

class Line{
public:
    Dot start, end;
    long double a, b, c;

    Line(Dot start, Dot end) : start(start), end(end) {
        a = end.y - start.y;
        b = end.x - start.x;
        c = start.y * (end.x - start.x) - start.x * (end.y - start.y);
    }

    Dot Interception(const Line &line) {
        long double d = (start.x - end.x) * (line.start.y - line.end.y) - (start.y - end.y) * (line.start.x - line.end.x);
        if(d == 0)
            return Dot(100000000, 100000000);
        long double dx = start.x * end.y - start.y * end.x;
        long double dy = line.start.x * line.end.y - line.start.y * line.end.x;
        Dot ans = Dot((dx * (line.start.x - line.end.x) - dy * (start.x - end.x)) / d, (dx * (line.start.y - line.end.y) - dy * (start.y - end.y)) / d);
        return isfinite(ans.x) ? ans : Dot(100000000, 100000000);
    }

    bool operator==(const Line &line) const{
        return start == line.start && end == line.end;
    }
};

double square(vector<int> face, vector<Dot> vert) {
    double square = 0;
    for(int i = 0; i < face.size() - 1; i++) {
        square += vert[face[i]].x * vert[face[i + 1]].y - vert[face[i]].y * vert[face[i + 1]].x;
    }
    square += vert[face[face.size() - 1]].x * vert[face[0]].y - vert[face[face.size() - 1]].y * vert[face[0]].x;
    return square / -2;
}

vector<double> calculateSquares(vector<vector<int>> faces, vector<Dot> vertices)
{
    vector<double> ans;
    size_t n = faces.size();
    vector<vector<bool>> was(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < faces[i].size(); j++) {
            if(!was[i][j])
            {
                was[i][j] = true;
                int v = faces[i][j];
                int prev = i;
                vector<int> cur_face;
                vector<int>::iterator iter;
                for(;;prev  = v, v = *iter) {
                    cur_face.push_back(v);
                    iter = lower_bound(faces[v].begin(), faces[v].end(), prev, [vertices, v](const int &a, const int &b) -> bool {
                        return atan2(vertices[b].y - vertices[v].y, vertices[b].x - vertices[v].x) > atan2(vertices[a].y - vertices[v].y, vertices[a].x - vertices[v].x);
                    });
                    if(++iter == faces[v].end()) {
                        iter = faces[v].begin();
                    }
                    if(was[v][iter-faces[v].begin()])
                        break;
                    was[v][iter-faces[v].begin()] = true;
                }
                double cur_square = square(cur_face, vertices);
                if(cur_square >= 1e-8)
                    ans.push_back(cur_square);

            }
        }
    }

    return ans;
}

int main()
{
    int n;
    cin >> n;


    vector<Line> lines;
    vector<vector<int>> faces;
    map<Dot, int> ids;
    vector<Dot> vertices;

    for(int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back(Line(Dot(x1, y1), Dot(x2, y2)));
    }

    if(n == 1 || n == 2)
        cout << 0 << endl;


    for(int i = 0; i < n; i++) {
        vector<Dot> intersections;
        for(int j = 0; j < n; j++) {
            Dot cur_inter = lines[i].Interception(lines[j]);
            if(cur_inter != Dot(100000000, 100000000)) {
                intersections.push_back(cur_inter);
                if (!ids.count(cur_inter)) {
                    ids[cur_inter] = (int)vertices.size();
                    vertices.push_back(cur_inter);
                    faces.resize (faces.size() + 1);
                }
            }
        }
        sort(intersections.begin(), intersections.end());

        if(intersections.size() == 0)
            continue;

        for(int j = 0; j < intersections.size() - 1; j++) {
            int x = ids[intersections[j]];
            int y = ids[intersections[j + 1]];
            if(x != y)
            {
                faces[x].push_back(y);
                faces[y].push_back(x);
            }
        }
    }

    n = faces.size();
    for(int i = 0; i < n; i++) {
        sort(faces[i].begin(), faces[i].end(), [vertices, i](const int &a, const int &b) -> bool {
            return atan2(vertices[b].y - vertices[i].y, vertices[b].x - vertices[i].x) > atan2(vertices[a].y - vertices[i].y, vertices[a].x - vertices[i].x);
        });
        faces[i].erase(unique(faces[i].begin(), faces[i].end()), faces[i].end());
    }

    vector<double> ans = calculateSquares(faces, vertices);
    cout.precision(20);
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for(double cur : ans) {
        cout << cur << endl;
    }

    return 0;
}
