#ifndef POINTS_H
#define POINTS_H

#include <cstdio>
#include "point.h"

struct points
{
    point_t *points_array;
    size_t len;
};

using points_t = struct points;

void points_init(points_t &points);
err_t read_number_of_points(points_t &points, FILE *file);
err_t read_points(points_t &points, FILE *file);
err_t allocate_array_of_points(points_t &points);
void free_array_of_points(points_t &points);
err_t read_all_points(points_t &points, FILE *file);
err_t transfer_all_points(points_t &points, const transfer_t &transfer);
err_t scale_all_points(points_t &points, const point_t &center, const scale_t &scale);
err_t turn_all_points(points_t &points, const point_t &center, const turn_t &turn);

#endif // POINTS_H
