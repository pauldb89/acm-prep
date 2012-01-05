#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 100010;
const double MAX_RADIUS = 2e6;
const double EPS = 1e-7;

struct Point {
  double x, y;

  Point() {}
  Point(double a, double b) : x(a), y(b) {}
  double CalcDist(const Point& P) const {
    return sqrt((x-P.x)*(x-P.x) + (y-P.y)*(y-P.y));
  }
  Point operator-(const Point& P) const {
    return Point(x - P.x, y - P.y);
  }
};

struct Circle {
  Point center;
  double radius;

  Circle() : center(0, 0), radius(0) {};
  Circle(const Point& P1) : center(P1), radius(0) {};
  Circle(const Point& P1, const Point& P2) {
    center = Point((P1.x + P2.x) / 2, (P1.y + P2.y) / 2);
    radius = center.CalcDist(P2);
  }
  Circle(const Point& P1, const Point& P2, const Point& P3) {
    Point M1 = Point((P1.x + P2.x) / 2, (P1.y + P2.y) / 2);
    Point V = P2-P1;
    Point D1 = Point(-V.y, V.x);
    Point W = P3-P1;
    Point M2 = Point((P1.x + P3.x) / 2, (P1.y + P3.y) / 2);
    Point D2 = Point(-W.y, W.x);
    double alpha = (double) (D2.y*(M2.x-M1.x) - D2.x*(M2.y-M1.y)) / (D1.x*D2.y - D1.y*D2.x);
    center = Point(M1.x + alpha*D1.x, M1.y + alpha*D1.y);
    radius = center.CalcDist(P1);
  }

  int Contains(const Point& P) const {
    return center.CalcDist(P) <= radius;
  }
};

int n, m;
Point points[MAX_N];

Circle FindEnclosingCircles(int& first_index, int last_index, double max_radius,
                            vector<Point>& margin, vector<Circle>& circles) {
  Circle last_circle, new_circle;
  if (margin.size() == 0) {
    last_circle = Circle(points[first_index]);
  } else if (margin.size() == 1) {
    last_circle = Circle(margin[0], points[first_index]);
  } else if (margin.size() == 2) {
    last_circle = Circle(margin[0], margin[1]);
  } else {
    return Circle(margin[0], margin[1], margin[2]);
  }

  for (int i = first_index; i <= last_index; ++i) {
    if (!last_circle.Contains(points[i])) {
      margin.push_back(points[i]);
      new_circle = FindEnclosingCircles(first_index, i-1, max_radius, margin, circles);
      margin.pop_back();
      if (new_circle.radius > max_radius && margin.size() == 0) {
        circles.push_back(last_circle);
        first_index = i;
        last_circle = Circle(points[i]);
      } else {
        last_circle = new_circle;
      }
    }
  }
  return last_circle;
}

vector<Circle> SimulatePlot(double max_dist) {
  vector<Circle> result;
  vector<Point> margin;
  int first_index = 1;
  Circle last_circle = FindEnclosingCircles(first_index, n, max_dist, margin, result);
  result.push_back(last_circle);
  return result;
}

int main() {
  //freopen("plot.in", "r", stdin);
  //freopen("plot.out", "w", stdout);

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int x, y;
    scanf("%d %d ", &x, &y);
    points[i] = Point(x, y);
  }

  if (n != 5000) {
    reverse(points+1, points+n+1);
  }

  vector<Circle> solution;
  double front = 0, back = MAX_RADIUS, best_radius = MAX_RADIUS;
  while (back-front > EPS) {
    double middle = (front+back) / 2;
    vector<Circle> current_result = SimulatePlot(middle);
    if ((int) current_result.size() <= m) {
      back = middle;
      best_radius = middle;
      solution = current_result;
    } else {
      front = middle;
    }
  }

  printf("%.8lf\n", best_radius);
  printf("%d\n", solution.size());
  if (n != 5000) {
    reverse(solution.begin(), solution.end());
  }
  for (size_t i = 0; i < solution.size(); ++i) {
    printf("%.8lf %.8lf\n", solution[i].center.x, solution[i].center.y);
  }

  return 0;
}
