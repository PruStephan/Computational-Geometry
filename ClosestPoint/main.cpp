#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Dot {
public:
    long long x, y;

    Dot(long long x, long long y) : x(x), y(y) {}
    Dot() : x(0), y(0) {}

    bool operator<(const Dot &a) const {
        return x < a.x || (x == a.x && y < a.y);
    }

    long long Distance(const Dot &a) const
    {

        return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y);
    }

    void print() {
        cout << x << " " << y;
    }
};

void merge_parts(vector<Dot> &dots, vector<Dot> &temp, long long l, long long m, long long r) {
    vector<Dot> left(dots.begin() + l, dots.begin() + m + 1);
    vector<Dot> right(dots.begin() + m + 1, dots.begin() + r + 1);
    long long i, cur_l, cur_r;
    for (i = l, cur_l = 0, cur_r = 0; cur_l < left.size() && cur_r < right.size(); i++) {
        if (left[cur_l].y <= right[cur_r].y) {
            temp[i] = left[cur_l++];
        } else {
            temp[i] = right[cur_r++];
        }
    }
    if(cur_l < left.size()) {
        copy(left.begin() + cur_l, left.end(), temp.begin() + i);
        i += left.size() - cur_l + 1;
    }
    if(cur_r < right.size())
        copy(right.begin() + cur_r, right.end(), temp.begin() + i);
}


void Search(vector<Dot> &dots, vector<Dot> &temp, long long l, long long r, pair<Dot, Dot> &ans, long long &min_dist) {
    if(r - l <= 3)
    {
        for(long long i = l; i <= r; i++) {
            for(long long j = i + 1; j <= r; j++)
            {
                long long dist = dots[i].Distance(dots[j]);
                if(dist < min_dist)
                {
                    min_dist = dist;
                    ans = make_pair(dots[i], dots[j]);
                }
            }
        }
        sort(dots.begin() + l, dots.begin() + r + 1, [](const Dot& a, const Dot& b) -> bool {
            return a.y < b.y;
        });
        return;
    }
    long long m = (l + r) / 2;
    long long x = dots[m].x;
    Search(dots, temp, l, m, ans, min_dist);
    Search(dots, temp,  m + 1, r, ans, min_dist);
    merge_parts(dots, temp, l, m, r);
    copy(temp.begin() + l, temp.begin() + r + 1, dots.begin() + l);
    for(long long i = l, t = 0; i <= r; i++)
    {
        if((dots[i].x - x) * (dots[i].x - x) < min_dist)
        {
            for(long long j = t - 1; j >= 0 && (dots[i].y - temp[j].y) * (dots[i].y - temp[j].y) < min_dist;  j--)
            {
                long long dist = dots[i].Distance(temp[j]);
                if(dist < min_dist) {
                    ans = make_pair(dots[i], temp[j]);
                    min_dist = dist;
                }
            }
            temp[t] = dots[i];
            t++;
        }
    }

}

int main() {
    long long n;
    cin >> n;
    vector<Dot> dots;
    for(long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        dots.push_back(Dot(x, y));
    }

    pair<Dot, Dot> ans(dots[0], dots[1]);
    long long min_dist =dots[0].Distance(dots[1]);
    sort(dots.begin(), dots.end());
    vector<Dot> tmp(n);
    Search(dots, tmp, 0, n - 1, ans, min_dist);
    ans.first.print();
    cout << " ";
    ans.second.print();

    return 0;
}