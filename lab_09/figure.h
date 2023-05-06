#ifndef FIGURE_H
#define FIGURE_H

#include <QListWidget>
#include "structures.h"

#define LEN 30

void initFigure(figure_t &figure, points_t &points, lines_t &lines, QColor color, bool isClose);
void initFigure(figure_t &figure, QColor color, bool isClose);
void addPointInFigure(figure_t &figure, Point point);
void addLineInFigure(figure_t &figure, Line line);
int isConvex(figure_t &cut);
void resetFigure(figure_t &figure);
void getLines(lines_t &lines, points_t &points);
void addPointInList(QListWidget *list, Point p);

#endif // FIGURE_H
