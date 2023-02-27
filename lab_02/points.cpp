#include "points.h"

void points_init(points_t &points)
{
    points.len = 0;
    points.points_array = NULL;
}

err_t read_number_of_points(points_t &points, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (fscanf(file, "%zu", &points.len) != 1)
        rc = READ_NUMBER_ERROR;
    else if (points.len <= 0)
        rc = INCORRECT_NUMBER;

    return rc;
}

err_t read_points(points_t &points, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (points.len <= 0)
        rc = INCORRECT_NUMBER;
    else if (points.points_array == NULL)
        rc = ALLOCATE_ERROR;
    else
        for (size_t i = 0; i < points.len; i++)
            rc = read_point(points.points_array[i], file);

    return rc;
}

err_t allocate_array_of_points(points_t &points)
{
    err_t rc = SUCCESS;

    if (points.len <= 0)
        rc = INCORRECT_NUMBER;
    else if ((points.points_array = (point_t *) malloc(sizeof(point_t) * points.len)) == NULL)
        rc = ALLOCATE_ERROR;

    return rc;
}

void free_array_of_points(points_t &points)
{
    free(points.points_array);
}

err_t read_all_points(points_t &points, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    if (! rc)
    {
        rc = read_number_of_points(points, file);
        if (! rc)
        {
            rc = allocate_array_of_points(points);
            if (rc)
                free_array_of_points(points);
            else
                rc = read_points(points, file);
           }
    }

    return rc;
}

err_t transfer_all_points(points_t &points, const transfer_t &transfer)
{
    err_t rc = SUCCESS;

    if (points.points_array == NULL || points.len <= 0)
        rc = EMPTY_POINTS_ERROR;
    else
        for (size_t i = 0; i < points.len; i++)
            transfer_point(points.points_array[i], transfer);

    return rc;
}

err_t scale_all_points(points_t &points, const point_t &center, const scale_t &scale)
{
    err_t rc = SUCCESS;

    if (points.points_array == NULL || points.len <= 0)
        rc = EMPTY_POINTS_ERROR;
    else
        for (size_t i = 0; i < points.len; i++)
            scale_point(points.points_array[i], center, scale);

    return rc;
}

err_t turn_all_points(points_t &points, const point_t &center, const turn_t &turn)
{
    err_t rc = SUCCESS;

    if (points.points_array == NULL || points.len <= 0)
        rc = EMPTY_POINTS_ERROR;
    else
        for (size_t i = 0; i < points.len; i++)
            turn_point(points.points_array[i], center, turn);

    return rc;
}
