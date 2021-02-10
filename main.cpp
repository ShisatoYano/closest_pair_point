#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
    int x, y;
};

int compare_x(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;

    return (p1->x - p2->x);
}

int compare_y(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;

    return (p1->y - p2->y);
}

float dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

float brute_force(Point P[], int n)
{
    float min = FLT_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dist(P[i], P[j]) < min) min = dist(P[i], P[j]);
        }
    }

    return min;
}

float min(float x, float y)
{
    return (x < y) ? x : y;
}

float strip_closest(Point strip[], int size, float d)
{
    float min = d;

    qsort(strip, size, sizeof(Point), compare_y);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            if (dist(strip[i], strip[j]) < min)
            {
                min = dist(strip[i], strip[j]);
            }
        }
    }

    return min;
}

float closest_util(Point P[], int n)
{
    if (n <= 3) return brute_force(P, n);

    int mid = n / 2;
    Point mid_point = P[mid];

    float dl = closest_util(P, mid);
    float dr = closest_util(P + mid, n - mid);

    float d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(P[i].x - mid_point.x) < d) strip[j] = P[i], j++;
    }

    return min(d, strip_closest(strip, j, d));
}

float closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compare_x);

    return closest_util(P, n);
}

int main() {
    Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1},
                 {12, 10}, {3, 4}};

    int n = sizeof(P) / sizeof(P[0]);

    cout << "The smallest distance is " << closest(P, n);

    return 0;
}
