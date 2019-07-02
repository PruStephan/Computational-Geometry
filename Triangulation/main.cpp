#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Dot{
public:
    double x, y;

    Dot(double x, double y) : x(x), y(y) {}

    bool operator==(const Dot &a) const {
        return a.x == x && a.y ==  y;
    }

    bool operator!=(const Dot &a) const {
        return !(*this == a);
    }

    bool operator<(const Dot &a) const {
        return (x < a.x) || (a.x == x && y < a.y);
    }
};

int LeftTurn(Dot a, Dot b, Dot c) {
    if((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0)
        return -1;
    if((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0)
        return 1;
    return 0;
}

class Triangle{
public:
    int a, b, c;
    Dot A, B, C;

    Triangle(int a, int b, int c, Dot A, Dot B, Dot C) : a(a), b(b), c(c), A(A), B(B), C(C){}

    bool belongs(Dot q) {
        return LeftTurn(A, B, q) >= 0 && LeftTurn(B, C, q) >= 0 && LeftTurn(C, A, q) >= 0;
    }

    void print() {
        cout << a + 1 << " " << b + 1 << " " << c + 1 << endl;
    }
};



vector<Triangle> Triangulate(vector<Dot> dots) {
    stack<int> vert;
    vector<Triangle> ans;
    for(int i = 0; i < dots.size(); i++) {
        vert.push(i);
        while(vert.size() > 2) {
            int c =  vert.top();
            vert.pop();
            int b =  vert.top();
            vert.pop();
            int a =  vert.top();
            vert.pop();
            Triangle cur(a, b, c, dots[a],dots[b],dots[c]);
            bool ear = true;
            if(LeftTurn(dots[a], dots[c], dots[b]) >= 0)
                ear = false;
            else {
                for (int j = 0; j < dots.size(); j++) {
                    if (dots[j] != dots[a] && dots[j] != dots[b] && dots[j] != dots[c])
                        if ((cur.belongs(dots[j]))) {
                        ear = false;
                        break;
                    }
                }
            }
            if(ear) {
                vert.push(a);
                vert.push(c);
                cur.print();
            } else {
                vert.push(a);
                vert.push(b);
                vert.push(c);
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<Dot> dots;

    for(int i = 0; i  < n; i++) {
        double x, y;
        cin >> x >> y;
        dots.push_back(Dot(x, y));
    }

    vector<Triangle> ans = Triangulate(dots);


    return 0;
}