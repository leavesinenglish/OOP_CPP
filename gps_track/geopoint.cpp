#include <cmath>
#include "geopoint.hpp"

using namespace std;

const double MAJOR_AXIS = 6378137.0,    // большая ось эллипсоида, м
MINOR_AXIS = 6356752.3142, // малая ось эллипсоида, м
MAJOR_AXIS_POW_2 = MAJOR_AXIS * MAJOR_AXIS,
        MINOR_AXIS_POW_2 = MINOR_AXIS * MINOR_AXIS,
        PI = 3.14159265358979323846264338327950288;

namespace {
    inline double deg2rad(double deg) {
        return deg * PI / 180.0;
    }

    inline double square(double x) { return x * x; }

    double trueAngle(const Geopoint &p)
    {
        return atan((MINOR_AXIS_POW_2 / MAJOR_AXIS_POW_2 *
                     tan(deg2rad(p.latitude()))));
    }

    // returns radius of small circle (radius between meridians)
    double pointRadius(const Geopoint &p, double true_angle)
    {
        return p.elevation() + 1.0 / sqrt(
                square(cos(true_angle)) / MAJOR_AXIS_POW_2 +
                square(sin(true_angle)) / MINOR_AXIS_POW_2);
    }

    double descartes(double x1, double y1, double x2, double y2)
    {
        x1 -= x2;
        y1 -= y2;

        return sqrt(x1*x1 + y1*y1);
    }
}

double Geopoint::distanceTo(const Geopoint &other) const
{
    double true_angle_1 = trueAngle(*this);
    double true_angle_2 = trueAngle(other);

    double point_radius_1 = pointRadius(*this, true_angle_1);
    double point_radius_2 = pointRadius(other, true_angle_2);

    double earth_point_1_x = point_radius_1 * cos(true_angle_1);
    double earth_point_1_y = point_radius_1 * sin(true_angle_1);

    double earth_point_2_x = point_radius_2 * cos(true_angle_2);
    double earth_point_2_y = point_radius_2 * sin(true_angle_2);

    double dx = descartes(earth_point_1_x, earth_point_1_y,
                          earth_point_2_x, earth_point_2_y);

    double dy = PI * (earth_point_1_x + earth_point_2_x) / 360.0 *
                (longitude() - other.longitude());

    return sqrt(square(dx) + square(dy));
}