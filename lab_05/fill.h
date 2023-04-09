#ifndef FILL_H
#define FILL_H

#include <vector>
#include "draw.h"

#define NOFITFIGURE -1

using edge_t = struct edge;

struct edge {
	double xWithScanLine;
	double dx;
	int scanLineNumber;
};

using edges_t = std::vector <edge_t>;

void fillFigure(figure_t &figure, QImage *image);
int getIndexCurFigure(figures_t &figures, figure_t &hole);
void drawFigures(figures_t &figures, QImage *image);

#endif // FILL_H
