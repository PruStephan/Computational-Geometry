 #include <algorithm>
#include <cstdio>
#include <cstdint>
#include <vector>

struct Vec2
{
    Vec2();
    Vec2(uint64_t id, int64_t x, int64_t y);
    
    uint64_t id;
    int64_t x;
    int64_t y;
};

Vec2::Vec2() = default;

Vec2::Vec2(uint64_t id, int64_t x, int64_t y) : id(id), x(x), y(y)
{
}

int64_t inline dist(const Vec2 & p1, const Vec2 & p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

struct comp_y
{
    const bool operator () (const Vec2 & v1, const Vec2 & v2) const
    {
        return v1.y < v2.y;
    }
};

struct comp_x
{
    const bool operator () (const Vec2 & v1, const Vec2 & v2) const
    {
        return v1.x < v2.x;
    }
};

struct KdNode
{
    KdNode(std::vector<Vec2>::iterator beg, std::vector<Vec2>::iterator end, uint64_t depth);
    ~KdNode();
    void nearest(const Vec2 & p, Vec2 & nearest_p, uint64_t depth) const;

    Vec2 p;
    KdNode * l = nullptr;
    KdNode * r = nullptr;
};

KdNode::KdNode(std::vector<Vec2>::iterator beg, std::vector<Vec2>::iterator end, uint64_t depth = 0)
{
    if (beg == end)
    {
        return;
    }
    if (beg + 1 == end)
    {
        p = *beg;
        return;
    }
    size_t med = (end - beg) / 2;
    if (depth & 1)
    {
        std::nth_element(beg, beg + med, end, comp_y());
    }
    else
    {
        std::nth_element(beg, beg + med, end, comp_x());
    }
    p = *(beg + med);
    if (med)
    {
        l = new KdNode(beg, beg + med, depth + 1);
    }
    if (end - beg - med - 1)
    {
        r = new KdNode(beg + med + 1, end, depth + 1);
    }
}

KdNode::~KdNode()
{
    delete l;
    delete r;
}

void KdNode::nearest(const Vec2 & req_p, Vec2 & nearest_p, const uint64_t depth = 0) const
{
    int64_t dist_to_node_p;
    if (depth & 1)
    {
        dist_to_node_p = req_p.y - p.y;
    }
    else
    {
        dist_to_node_p = req_p.x - p.x;
    }
    KdNode * near_node;
    KdNode * far_node;
    if (dist_to_node_p > 0)
    {
        near_node = r;
        far_node = l;
    }
    else
    {
        near_node = l;
        far_node = r;
    }
    if (near_node)
    {
        near_node->nearest(req_p, nearest_p, depth + 1);
    }
    if (dist_to_node_p * dist_to_node_p < dist(req_p, nearest_p) && far_node)
    {
        far_node->nearest(req_p, nearest_p, depth + 1);
    }
    if (dist(req_p, p) < dist(req_p, nearest_p))
    {
        nearest_p = p;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    size_t n, m;
    scanf("%lu %lu", &n, &m);
    std::vector<Vec2> points(n);
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%ld %ld", &points[i].x, &points[i].y);
        points[i].id = i + 1;
    }
    KdNode kd_tree(points.begin(), points.end());
    for (size_t i = 0; i < m; ++i)
    {
        Vec2 req_p;
        scanf("%ld %ld", &req_p.x, &req_p.y);
        Vec2 nearest_p = points[points.size() / 2];
        kd_tree.nearest(req_p, nearest_p);
        printf("%lu\n", nearest_p.id);
    }
    return 0;
}
