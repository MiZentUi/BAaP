#include <iostream>
#include "cmath.h"

double side(double x1, double y1, double x2, double y2) { return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); }

double area_from_heron(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_from_height(double a, double h) { return 0.5 * a * h; }

double area_from_r(double a, double b, double c, double r) { return r * (a + b + c) / 2; }

double area_from_R(double a, double b, double c, double R) { return a * b * c / (4 * R); }

double height(double a, double s) { return (2 * s) / a; }

double median(double a, double b, double c) { return 0.5 * std::sqrt(2 * a * a + 2 * b * b - c * c); }

double bisector(double a, double b, double c) { return std::sqrt(a * b * (a + b + c) * (a + b - c)) / (a + b); };

double corner(double a, double b, double c) { return std::acos((b * b + c * c - a * a) / (2 * b * c)); }

double rad_to_deg(double rad) { return rad * 180 / M_PI; }

int main(int argc, char const *argv[])
{
    double x1, y1, x2, y2, x3, y3;
    std::cout << "(x1 y1 x2 y2 x3 y3):\t";
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    double a = side(x1, y1, x2, y2);
    double b = side(x2, y2, x3, y3);
    double c = side(x1, y1, x3, y3);
    double s = area_from_heron(a, b, c);
    double ha = height(a, s), hb = height(b, s), hc = height(c, s);
    double ma = median(b, c, a), mb = median(a, c, b), mc = median(a, b, c);
    double ba = bisector(b, c, a), bb = bisector(a, c, b), bc = bisector(a, b, c);
    double ca = corner(a, b, c), cb = corner(b, a, c), cc = corner(c, a, b);
    double r = 2 * s / (a + b + c), R = a * b * c / (4 * s);
    std::cout << "Sides:\t\t\t{" << "A: " << a << ", B: " << b << ", C: " << c << "}" << std::endl;
    std::cout << "Heights:\t\t{" << "A: " << ha << ", B: " << hb << ", C: " << hc << "}" << std::endl;
    std::cout << "Medians:\t\t{" << "A: " << ma << ", B: " << mb << ", C: " << mc << "}" << std::endl;
    std::cout << "Bisectors:\t\t{" << "A: " << ba << ", B: " << bb << ", C: " << bc << "}" << std::endl;
    std::cout << "Corners (RAD):\t\t{" << "A: " << ca << ", B: " << cb << ", C: " << cc << "}" << std::endl;
    std::cout << "Corners (DEG):\t\t{" << "A: " << rad_to_deg(ca) << ", B: " << rad_to_deg(cb) << ", C: " << rad_to_deg(cc) << "}" << std::endl;
    std::cout << "r:\t\t\t" << r << std::endl;
    std::cout << "R:\t\t\t" << R << std::endl;
    std::cout << "Sr:\t\t\t" << M_PI * r * r << std::endl;
    std::cout << "Cr:\t\t\t" << 2 * M_PI * r << std::endl;
    std::cout << "SR:\t\t\t" << M_PI * R * R << std::endl;
    std::cout << "CR:\t\t\t" << 2 * M_PI * R << std::endl;
    std::cout << "Area from Heron:\t" << area_from_heron(a, b, c) << std::endl;
    std::cout << "Area from height:\t" << area_from_height(a, ha) << std::endl;
    std::cout << "Area from r:\t\t" << area_from_r(a, b, c, r) << std::endl;
    std::cout << "Area from R:\t\t" << area_from_R(a, b, c, R) << std::endl;
    std::cout << "Perimeter:\t\t" << a + b + c << std::endl;
    return 0;
}