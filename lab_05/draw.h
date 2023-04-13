#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include <QPainter>
#include <QTime>
#include <QCoreApplication>
#include "structures.h"

void draw_point(const point_t &point, const QColor color, QImage *image);
void drawLine(const line_segment_t &line, QImage *image);
void removePointFromScene(const point_t &point, QImage *image);
void drawStr(const int x1, const int x2, const int y, const QColor color, QImage *image);
void drawCountour(lines_t &lines, QImage *image);
void swapPoints(line_segment_t &line);
void initPoint(point_t &point, const int x, const int y);
void initLine(line_segment_t &line, const point_t start, const point_t finish, const QColor color);
void initFigure(figure_t &figure, const lines_t lines, const points_t points, const QColor fill,
				const QColor border, bool isClosed, const figures_t holes);
void updateLinesColor(lines_t &lines, QColor color);
void removePointFromFigure(figures_t &figures, point_t &remPoint);
int countLinesContainPoint(lines_t &lines, point_t &point);
int getFigureFromPoints(figures_t &figures, points_t &points);

#endif // DRAW_H
