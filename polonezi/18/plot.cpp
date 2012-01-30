#include <algorithm>
#include <cassert>
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
    double d1 = P1.CalcDist(P2);
    double d2 = P1.CalcDist(P3);
    double d3 = P2.CalcDist(P3);
    if (fabs(d1+d2-d3) <= EPS) {
      Circle circle(P2, P3);
      center = circle.center;
      radius = circle.radius;
    } else if (fabs(d1+d3-d2) <= EPS) {
      Circle circle(P1, P3);
      center = circle.center;
      radius = circle.radius;
    } else if (fabs(d2+d3-d1) <= EPS) {
      Circle circle(P1, P2);
      center = circle.center;
      radius = circle.radius;
    } else {
      Point M1 = Point((P1.x + P2.x) / 2, (P1.y + P2.y) / 2);
      Point V = P2-P1;
      Point D1 = Point(-V.y, V.x);
      Point W = P3-P1;
      Point M2 = Point((P1.x + P3.x) / 2, (P1.y + P3.y) / 2);
      Point D2 = Point(-W.y, W.x);
      assert(fabs(D1.x*D2.y - D1.y*D2.x) > EPS);
      double alpha = (D2.y*(M2.x-M1.x) - D2.x*(M2.y-M1.y)) / (D1.x*D2.y - D1.y*D2.x);
      center = Point(M1.x + alpha*D1.x, M1.y + alpha*D1.y);
      radius = center.CalcDist(P1);
      assert(fabs(radius - center.CalcDist(P2)) < EPS);
      assert(fabs(radius - center.CalcDist(P3)) < EPS);
    }
  }

  int Contains(const Point& P) const {
    return center.CalcDist(P) <= radius + EPS;
  }
};

int n, m;
Point points[MAX_N];

Circle MinimumEnclosingCircle(
    const vector<int>& indexes, int current_index, vector<Point>& margin) {
  Circle circle;
  if (margin.size() == 0) {
    circle = Circle(points[indexes[0]]);
  } else if (margin.size() == 1) {
    circle = Circle(margin[0], points[indexes[0]]);
  } else if (margin.size() == 2) {
    circle = Circle(margin[0], margin[1]);
  } else {
    return Circle(margin[0], margin[1], margin[2]);
  }

  for (int i = 0; i < current_index; ++i) {
    if (!circle.Contains(points[indexes[i]])) {
      margin.push_back(points[indexes[i]]);
      circle = MinimumEnclosingCircle(indexes, i, margin);
      margin.pop_back();
    }
  }
  return circle;
}

Circle MinimumEnclosingCircle(int first_index, int last_index) {
  vector<int> indexes;
  for (int i = first_index; i <= last_index; ++i) {
    indexes.push_back(i);
  }
  random_shuffle(indexes.begin(), indexes.end());
  vector<Point> margin;
  return MinimumEnclosingCircle(indexes, indexes.size(), margin);
}

vector<Circle> SimulatePlot(double max_radius) {
  vector<Circle> result;
  int last_index = 0;
  while (last_index < n && (int) result.size() <= m) {
    int step = 1;
    while (last_index + step <= n &&
           MinimumEnclosingCircle(last_index+1, last_index + step).radius <= max_radius) {
      step *= 2;
    }

    int front = last_index + step/2, back = min(n, last_index + step);
    int new_index = last_index + step/2;
    while (front <= back) {
      int middle = (front+back) / 2;
      if (MinimumEnclosingCircle(last_index+1, middle).radius <= max_radius) {
        new_index = middle;
        front = middle+1;
      } else {
        back = middle-1;
      }
    }
    result.push_back(MinimumEnclosingCircle(last_index+1, new_index));
    last_index = new_index;
  }
  return result;
}

int main() {
//  freopen("plot.in", "r", stdin);
//  freopen("plot.out", "w", stdout);

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int x, y;
    scanf("%d %d ", &x, &y);
    points[i] = Point(x, y);
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
  for (size_t i = 0; i < solution.size(); ++i) {
    printf("%.8lf %.8lf\n", solution[i].center.x, solution[i].center.y);
  }

  return 0;
}
