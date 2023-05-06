#ifndef CLIP_H
#define CLIP_H

#include <vector>
#include "structures.h"
#define MATRIX_SIZE 2
#define PARAM_SIZE 1

bool isVisible(Line src, Point p, int norm);
bool findInter(Point &p, Line src, Line sec, int norm);
void addInterPoint(points_t *result, int *nRes, Point interP);
points_t clip(points_t &poly, figure_t &clipper);
int checkConvex(figure_t &cut);

#endif // CLIP_H
