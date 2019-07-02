#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <cstdlib>


using  namespace std;

class Dot {
public:
    double x;
    double y;

    Dot() : x(0), y(0) {}
    Dot(double x, double y) : x(x), y(y) {}

    void operator=(Dot a) {
        x = a.x;
        y = a.y;
    }


    bool operator==(Dot a) {
        return a.x == x && a.y == y;
    }
};

class Circle {
public:
    Dot centre;
    double radius;

    Circle(double radius, Dot centre) : radius(radius), centre(centre) {}

    void Resize(double new_radius) {
        radius = new_radius;
    }

    bool belongs(Dot q) {
        double res = sqrt((q.x - centre.x) * (q.x - centre.x) + (q.y  - centre.y) * (q.y - centre.y));
        return res <= radius;
    }

    void operator=(Circle a) {
        centre = a.centre;
        radius = a.radius;
    }
};

Dot max(Dot a, Dot b) {
    if(a.x > b.x)
        return a;
    if(a.x < b.x)
        return b;
    if(a.y > b.y)
        return a;
    else
        return b;
}

Dot min(Dot a, Dot b) {
    if(a.x < b.x)
        return a;
    if(a.x > b.x)
        return b;
    if(a.y < b.y)
        return a;
    else
        return b;
}

Circle createBy3Dots(Dot a, Dot b, Dot c) {
    double x1 = a.x;
    double x2 = b.x;
    double x3 = c.x;

    double y1 = a.y;
    double y2 = b.y;
    double y3 = c.y;

    double A = x2 - x1;
    double B = y2 - y1;
    double C = x3 - x1;
    double D = y3 - y1;
    double E = A * (x1 + x2) + B * (y1 + y2);
    double F = C * (x1 + x3) + D * (y1 + y3);
    double G = 2 * (A * (y3 - y2) - B * (x3 - x2));
    if(G == 0) {
        Dot p1 = max(a, max(b, c));
        Dot p2 = min(a, min(b, c));
        return Circle(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)), Dot((p1.x + p2.x) / 2, (p1.y+ p2.y) / 2));
    }

    double Cx = (D * E - B * F) / G;
    double Cy = (A * F - C * E) / G;

    double r = sqrt((Cx - a.x) * (Cx - a.x) + (Cy - a.y) * (Cy - a.y));

    return Circle(r, Dot(Cx, Cy));
}

Circle createCircle3(vector<Dot> cities, Dot p1, Dot p2, int k) {
    Circle start(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) / 2, Dot((p1.x + p2.x) / 2, (p1.y+ p2.y) / 2));
    for(int i = 0; i < k; i++) {
        if(!start.belongs(cities[i]))
            start = createBy3Dots(p1, p2, cities[i]);
    }
    return start;
}

Circle createCircle2(vector<Dot> cities_part, Dot p1, int k) {
    shuffle(cities_part.begin(), cities_part.begin() + k, std::default_random_engine(1235324));
    Dot p2 = cities_part[0];
    Circle start(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) / 2, Dot((p1.x + p2.x) / 2, (p1.y+ p2.y) / 2));
    for(int i = 1; i < k; i++) {
        if(!start.belongs(cities_part[i]))
            start = createCircle3(cities_part, p1, cities_part[i], i);
    }
    return start;
}

Circle createCircle(vector<Dot> cities) {
    shuffle(cities.begin(), cities.end(), std::default_random_engine(3753979135));
    Dot p1 = cities[0];
    Dot p2 = cities[1];
    Circle start(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) / 2, Dot((p1.x + p2.x) / 2, (p1.y+ p2.y) / 2));
    for(int i = 2; i < cities.size(); i++)
    {
        if(!start.belongs(cities[i]))
            start = createCircle2(cities, cities[i], i);
    }
    return start;
}

Circle createCircleIterative(vector<Dot> cities) {
    shuffle(cities.begin(), cities.end(), std::default_random_engine(877152));
    Circle start = Circle(sqrt((cities[0].x - cities[1].x) * (cities[0].x - cities[1].x) + (cities[0].y - cities[1].y) * (cities[0].y - cities[1].y)) / 2, Dot((cities[0].x+ cities[1].x) / 2, (cities[0].y+ cities[1].y) / 2));
    for(int i = 2; i < cities.size(); i++)
    {
        if(!start.belongs(cities[i])) {
            Dot q = cities[i];
            vector<Dot> cities2(cities.begin(), cities.begin() + i);
            shuffle(cities2.begin(), cities2.end(), std::default_random_engine(877152));
            Dot p = cities2[0];
            start = Circle(sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y)) / 2, Dot((q.x+ p.x) / 2, (p.y+ q.y) / 2));
            for(int j = 1; j < cities2.size(); j++) {
                if(!start.belongs(cities2[j]))
                {
                    vector<Dot> cities3(cities2.begin(), cities2.begin() + j);
                    Dot p1 = cities2[j];
                    Dot q1 = q;
                    start = Circle(sqrt((q1.x - p1.x) * (q1.x - p1.x) + (p1.y -q1.y) * (p1.y - q1.y)) / 2, Dot((q1.x+ p1.x) / 2, (p1.y+ q1.y) / 2));
                    for(int k = 0; k < cities3.size(); k++) {
                        if(!start.belongs(cities3[k]))
                            start = createBy3Dots(cities3[k], p1, q1);
                    }
                }
            }
        }
    }
    return start;
}


int main() {

    int n;
    cin >> n;
    vector<Dot> cities(n);

    for(int i = 0; i < n; i++) {
        scanf("%lf%lf", &cities[i].x, &cities[i].y);
    }

    cout.precision(20);

    if(n == 1) {
        printf("0\n%.20lf %.20lf", cities[0].x, cities[0].y);
        return 0;
    }

    Circle ans(0, {0,0});

    //Circle ans = createCircle(cities);
    //printf("%.20lf\n%.20lf %.20lf\n", ans.radius, ans.centre.x, ans.centre.y);

    ans = createCircleIterative(cities);
    printf("%.20lf\n%.20lf %.20lf", ans.radius, ans.centre.x, ans.centre.y);


    return 0;
}