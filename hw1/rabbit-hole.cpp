#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::abs;

using namespace std;

#define ll long long
#define ld long double
#define Point pair<ll, ll>

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void print_vect(vector<Point>& vect) {
  for(Point v : vect)
    cout << '(' << v.first << ", " << v.second << ") \n";
}

int orientation(Point p1, Point p2, Point p) {
  ll val = (p2.second - p1.second) * (p.first - p2.first) - (p2.first - p1.first) * (p.second - p2.second);

  if(val == 0) // collinear
    return 0;

  return (val > 0) ? 1 : -1; // 1 for clockwise, -1 for counterclockwise
}

ld distance_to_line(Point p1, Point p2, Point p) {
  return abs((p2.first - p1.first) * (p1.second - p.second) -
             (p1.first - p.first) * (p2.second - p1.second)) /
         sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

void quick_hull(vector<Point>& points, int n, Point p1, Point p2, vector<Point>& hull) {
  int ind = -1;
  ld max_distance = 0;
  for(int i = 0; i < n; i++) {
    ld distance = distance_to_line(p1, p2, points[i]);  

    if(orientation(p1, p2, points[i]) == -1 && distance > max_distance) {
      ind = i;
      max_distance = distance;
    }
  }

  // no points left
  if(ind == -1) {
    hull.push_back(p1);
    hull.push_back(p2);
    return;
  }

  quick_hull(points, n, p1, points[ind], hull);
  quick_hull(points, n, points[ind], p2, hull);
}

vector<Point> convex_hull(vector<Point>& points, ll n) {
  if(n < 3)
    return points;
  
  // find the leftmost and rightmost points
  int min_x = 0, max_x = 0;
  for(int i = 1; i < n; i++) {
    if(points[i] < points[min_x])
      min_x = i;
    if(points[i] > points[max_x])
      max_x = i;
  }

  vector<Point> hull;
  quick_hull(points, n, points[min_x], points[max_x], hull);
  quick_hull(points, n, points[max_x], points[min_x], hull);

  return hull;
}

ll polygon_area(vector<Point>& hull, int n) {
  Point ref({0, 0});
  for(int i = 0; i < n; i++) {
    ref.first += hull[i].first;
    ref.second += hull[i].second;
  }
  ref.first  /= n;
  ref.second /= n;

  sort(hull.begin(), hull.end(), [&](Point a, Point b) {
    ld angleA = atan2(a.second - ref.second, a.first - ref.first);
    ld angleB = atan2(b.second - ref.second, b.first - ref.first);
    return angleA < angleB;
  });

  ll area = 0;
  for(int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += (hull[i].first * hull[j].second) - (hull[j].first * hull[i].second);
  }

  return llabs(area);
}

int main() {
  fast_io();

  int hole_num;
  cin >> hole_num;

  vector<Point> points(hole_num);
  for(Point &point : points)
    cin >> point.first >> point.second;

  vector<Point> hull = convex_hull(points, hole_num);
  sort(hull.begin(), hull.end());
  hull.erase(unique(hull.begin(), hull.end()), hull.end());

  ll area_sqr = polygon_area(hull, hull.size());
  bool odd = (area_sqr % 2 == 1);

  ll area = area_sqr / 2;
  cout << fixed << area;
  if(odd) cout << ".5";

  return 0;
}
