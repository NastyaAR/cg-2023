#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include "model.h"

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using canvas_t = struct canvas;

void clear_canvas(const canvas_t &canvas);
point_t transform(const canvas_t &canvas, point_t point);
void draw_line(const canvas_t &canvas, facet_t facet, point_t *points_array);
err_t draw_lines(const canvas_t &canvas, points_t &points, facets_t &facets);
err_t draw_model(const canvas_t &canvas, model_t &model);

#endif // CANVAS_H

