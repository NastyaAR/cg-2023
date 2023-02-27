#include "point.h"

void point_init(point_t &point)
{
    point.x = 0;
    point.y = 0;
}

err_t read_point(point_t &point, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (fscanf(file, "%lf %lf", &point.x, &point.y) != 2)
        rc = READ_POINT_ERROR;

    return rc;
}

void transfer_point(point_t &point, const transfer_t &transfer)
{
    point.x += transfer.dx;
    point.y += transfer.dy;
}

void scale_point(point_t &point, const point_t center, const scale_t &scale)
{
    point.x = center.x + scale.kx * (point.x - center.x);
    point.y = center.y + scale.ky * (point.y - center.y);
}

double to_radians(const double angle)
{
    return M_PI / 180 * angle;
}

void turn_point(point_t &point, const point_t center, const turn_t &turn)
{
    double radians = to_radians(turn.d0);
    double cos_angle = cos(radians);
    double sin_angle = sin(radians);
    double temp_y = point.y;
    double temp_x = point.x;


    point.x = (temp_y - center.y)  * sin_angle + (temp_x - center.x) * cos_angle + center.x;
    point.y = -(temp_x - center.x) * sin_angle + (temp_y - center.y) * cos_angle + center.y;
}
