#include "model.h"

model_t &model_init(void)
{
    static model_t tmp_figure;

    point_init(tmp_figure.center);
    points_init(tmp_figure.points);
    facets_init(tmp_figure.facets);

    return tmp_figure;
}

err_t load_model(model_t &model, const char *filename)
{
    err_t rc = SUCCESS;

    if (filename == NULL)
        rc = FILE_NAME_ERROR;
    else
    {
        FILE *file = fopen(filename, "r");
        if (file == NULL)
            rc = FILE_OPEN_ERROR;
        else
        {
            rc = read_model(model, file);
            if (rc)
                free_model(model);
            fclose(file);
        }
    }

    return rc;
}

err_t read_model(model_t &model, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = read_point(model.center, file);
        rc = read_all_points(model.points, file);

        if (! rc)
        {
            rc = read_all_facets(model.facets, file);
            if (rc)
                free_array_of_points(model.points);
        }
    }

    return rc;
}

void free_model(model_t &model)
{
    free_array_of_points(model.points);
    free_array_of_facets(model.facets);
}

err_t transfer_model(model_t &model, const transfer_t &transfer)
{
    transfer_point(model.center, transfer);
    err_t rc = transfer_all_points(model.points, transfer);

    return rc;
}

err_t scale_model(model_t &model, const scale_t &scale)
{
    err_t rc = scale_all_points(model.points, scale.center, scale);
    return rc;
}

err_t turn_model(model_t &model, const turn_t &turn)
{
    err_t rc = turn_all_points(model.points, turn.center, turn);
    return rc;
}

void delete_model(model_t &model)
{
    free_array_of_points(model.points);
    free_array_of_facets(model.facets);
}

point_t save_model(model_t &model)
{
    const char *filename = "tmp.txt";

    FILE *file = fopen(filename, "w");
    fprintf(file, "%lf %lf\n%zu\n", model.center.x, model.center.y, model.points.len);
    for (size_t i = 0; i < model.points.len; i++)
        fprintf(file, "%lf %lf\n", model.points.points_array[i].x, model.points.points_array[i].y);

    fprintf(file, "%zu\n", model.facets.len);
    for (size_t i = 0; i < model.facets.len; i++)
        fprintf(file, "%d %d\n", model.facets.facets_array[i].point_1, model.facets.facets_array[i].point_2);

    fclose(file);

    return model.center;
}
