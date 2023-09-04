#ifndef SUPERELLIPSE_H
#define SUPERELLIPSE_H

# include "Graph.h"
# include <assert.h>
# include <vector>
# include <cmath>

using namespace Graph_lib;
using namespace std;

class Hyperelliptic : public Shape {
  private:
    double a, b, m, n;
    int N;

    Point center;

    vector <Point> points;

    Color lcolor;
    Line_style ls;

    void draw_lines() const;

  public:
    Hyperelliptic(double a, double b, double m, double n, int N , Point center);

    ~ Hyperelliptic() { };
};

Hyperelliptic :: Hyperelliptic(double a, double b, double m, double n, int N, Point center) :
  a(a), b(b), m(m), n(n), N(N), center(center),
  lcolor(fl_color()), ls(0) {
      points.clear();
      // range is [-a, a]
      double x = -a, step = a * 2 / N;
      for (int i = 0; i <= N; ++ i) {
        double y1 = pow(1 - pow(fabs(x / a), n), 1.0 / m) * b;
        double y2 = -y1;
        points.push_back(Point(x+center.x, y1+center.y));
        if(i != 0 && i != N) points.push_back(Point(x+center.x, y2+center.y));
        x += step;
      }
  }


void Hyperelliptic :: draw_lines() const {
    for (int i = 0; i < points.size(); ++ i)
      for (int j = i + 1; j < points.size(); ++ j)
        fl_line(points[i].x, points[i].y, points[j].x, points[j].y);
}

# endif
