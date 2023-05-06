#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "structures.h"

#define COEF 2

void drawPoint(Point p, QPainter *paint);
void drawLine(Line line, QPainter *paint);
void drawFigure(figure_t &figure, QPainter *paint);
void draw(figure_t &clipper, figure_t &figure, figure_t &resFigure, QPainter *painter, currentColors colors);

#endif // DRAW_H
