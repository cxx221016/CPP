# ifndef _RIGHT_TRIANGLE_H_
# define _RIGHT_TRIANGLE_H_

# include "Graph.h"
# include <assert.h>
# include <vector>
# include <cmath>

using namespace Graph_lib;
using namespace std;

#define PI 3.1415926

class RightTriangle : public Closed_polyline {
  private:
    vector <Point> points;
    double a, b;
    Point c;
    double angle;              // angle means the longest edge's angle

    Color lcolor;
    Line_style ls;

    Point zoomPoint(double ox, double oy);

  public:
    RightTriangle(Point c, double a, double b, double angle = 0.0);

    ~ RightTriangle() { }
};

# include "righttriangle.h"

RightTriangle :: RightTriangle(Point c, double a, double b, double angle) :
  c(c), a(a), b(b), angle(angle), lcolor(fl_color()), ls(0) {
    //calculate();
    double beta = atan(a / b);
    add(Point(c.x, c.y));
    add(Point(c.x + a * cos(angle - beta), c.y + a * sin(angle - beta)));
    add(Point(c.x + b * cos(angle - beta + PI / 2), c.y + b * sin(angle - beta + PI / 2)));
  }

# endif