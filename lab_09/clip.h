#ifndef CLIP_H
#define CLIP_H

#include <vector>
#include "structures.h"
#define MATRIX_SIZE 2
#define PARAM_SIZE 1

int isVisible(Point point, Line line);
Point getInterPoint(Line line1 , Line line2);
bool isInter(Line line1, Line line2);
void addInterPoint(points_t *result, int *nRes, Point interP);
void copyResult(points_t &poly, points_t &result);
points_t clip(points_t &poly, points_t &clipper);

#endif // CLIP_H
