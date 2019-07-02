#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

class Dot {
public:
    long long x, y;
    int num;

    Dot(long  long x, long long y) : x(x), y(y), num(-1){}
    Dot(long  long x, long long y, int num) : x(x), y(y), num(num){}

    bool operator<(const Dot &a) {
        return (x < a.x) || (x == a.x && y < a.y);
    }

    long long dist(const Dot &a) const {
        return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y);
    }
};

class Node {
public:
    Dot border;
    bool leaf;
    Node *topLeft;
    Node *bottomRight;

    Node(Dot border, bool leaf) : border(border), leaf(leaf), topLeft(nullptr), bottomRight(nullptr) {};
    Node(Dot border, bool leaf, Node* one, Node * two) :border(border), leaf(leaf), topLeft(one), bottomRight(two) {};
};

Node *root;

Node* createTree(vector<Dot> dots, bool even) {
    if (dots.size() == 1) {
        return new Node(dots[0], true);
    }
    if(dots.size() == 0)
        return nullptr;
    if (even) {
        int m = dots.size() / 2 - 1;
        nth_element(dots.begin(), dots.begin() + m, dots.end(), [](const Dot &a, const Dot &b) -> bool {
            return a.x < b.x;
        });
        Node *left = createTree(vector<Dot>(dots.begin(), dots.begin() + m), !even);
        Node *right = nullptr;
        if(m + 1< dots.size()) {
            right = createTree(vector<Dot>(dots.begin() + m + 1, dots.end()), !even);
        }
        return new Node(dots[m], false, left, right);



    } else
    {
        int m = dots.size() / 2 - 1;
        nth_element(dots.begin(), dots.begin() + m, dots.end(), [](const Dot &a, const Dot &b) -> bool {
            return a.y< b.y;
        });

        Node *left = createTree(vector<Dot>(dots.begin(), dots.begin() + m), !even);
        Node *right = nullptr;
        if(m + 1 < dots.size()) {
            right = createTree(vector<Dot>(dots.begin() + m + 1, dots.end()), !even);
        }
        return new Node(dots[m], false, left, right);

    }
}

void Search(Node * cur, Dot q, long long &cur_dist, bool even, int &num) {
    long long dist = q.dist(cur->border);
    if(dist < cur_dist) {
        cur_dist = dist;
        num = cur->border.num;
    }
    if(cur->leaf)
        return;

    if(even)
    {
        long long border_dist = abs(q.x - cur->border.x);
        if(q.x <= cur->border.x) {
            if(cur->topLeft != nullptr)
                Search(cur->topLeft, q, cur_dist, !even, num);
            if(cur->bottomRight != nullptr && border_dist * border_dist < cur_dist) {
                Search(cur->bottomRight, q, cur_dist, !even, num);
            }
        } else {
            if(cur->bottomRight != nullptr)
                Search(cur->bottomRight, q, cur_dist, !even, num);
            if(cur->topLeft != nullptr && border_dist * border_dist < cur_dist) {
                Search(cur->topLeft, q, cur_dist, !even, num);
            }
        }
    }
    else
    {
        long long border_dist = abs(q.y - cur->border.y);
        if(q.y <= cur->border.y) {
            if (cur->topLeft != nullptr)
                Search(cur->topLeft, q, cur_dist, !even, num);
            if (cur->bottomRight != nullptr && border_dist * border_dist < cur_dist) {
                Search(cur->bottomRight, q, cur_dist, !even, num);
            }
        }else {
            if(cur->bottomRight != nullptr)
                Search(cur->bottomRight, q, cur_dist, !even, num);
            if(cur->topLeft != nullptr && border_dist * border_dist < cur_dist) {
                Search(cur->topLeft, q, cur_dist, !even, num);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Dot> dots;
    for(int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        dots.push_back(Dot(x, y, i + 1));
    }

    root = createTree(dots, true);
    for(int i = 0; i < m; i++) {
        long long x, y;
        cin >> x >> y;
        int num = -1;
        long long cur_dist = 10000000000;
        Search(root, Dot(x, y), cur_dist, true, num);
        cout << num << endl;
    }

    return 0;
}