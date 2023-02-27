#ifndef POINT_H
#define POINT_H

#include <cstdio>
#include <cstdlib>
#include "math.h"
#include "errors.h"

struct point
{
    double x;
    double y;
};

using point_t = struct point;

struct transfer
{
    double dx;
    double dy;
};

using transfer_t = struct transfer;

struct scale
{
    double kx;
    double ky;
    point_t center;
};

using scale_t = struct scale;

struct turn
{
    double d0;
    point_t center;
};

using turn_t = struct turn;

void point_init(point_t &point);
err_t read_point(point_t &point, FILE *file);
void transfer_point(point_t &point, const transfer_t &transfer);
void scale_point(point_t &point, const point_t center, const scale_t &scale);
void turn_point(point_t &point, const point_t center, const turn_t &turn);
double to_radians(const double angle);

#endif // POINT_H
