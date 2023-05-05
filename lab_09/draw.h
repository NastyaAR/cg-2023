#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "structures.h"

#define COEF 2

void drawPoint(Point p, QPainter *paint);
void drawLine(Line line, QPainter *paint);
void drawFigure(figure_t &figure, QPainter *paint);

#endif // DRAW_H
