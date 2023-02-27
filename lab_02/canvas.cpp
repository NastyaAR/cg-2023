#include "canvas.h"

void clear_canvas(const canvas_t &canvas)
{
    canvas.scene->clear();
}

void draw_line(const canvas_t &canvas, facet_t facet, point_t *points_array)
{
    point_t point1 = transform(canvas, points_array[facet.point_1]);
    point_t point2 = transform(canvas, points_array[facet.point_2]);

    canvas.scene->addLine(point1.x, point1.y, point2.x, point2.y);
}

point_t transform(const canvas_t &canvas, point_t point)
{
    point.x += canvas.height / 2;
    point.y += canvas.width / 2;

    return point;
}

err_t draw_lines(const canvas_t &canvas, points_t &points, facets_t &facets)
{
    err_t rc = SUCCESS;

    if (points.points_array == NULL || facets.facets_array == NULL || points.len <= 0 || facets.len <= 0)
        rc = DRAW_LINKS_ERROR;
    else
        for (size_t i = 0; i < facets.len; i++)
            draw_line(canvas, facets.facets_array[i], points.points_array);

    return rc;
}

err_t draw_model(const canvas_t &canvas, model_t &model)
{
    clear_canvas(canvas);
    err_t rc = draw_lines(canvas, model.points, model.facets);

    return rc;
}
