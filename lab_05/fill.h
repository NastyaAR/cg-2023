#ifndef FILL_H
#define FILL_H

#include <vector>
#include <QGraphicsPixmapItem>
#include "draw.h"

#define NOFITFIGURE -1

using edge_t = struct edge;

struct edge {
	double xWithScanLine;
	double dx;
	int scanLineNumber;
};

using edges_t = std::vector <edge_t>;

void fillFigure(figure_t &figure, QImage *image, QGraphicsScene *scene, double delay=0.0);
int getIndexCurFigure(figures_t &figures, figure_t &hole);
void drawFigures(figures_t &figures, QImage *image, QGraphicsScene *scene, bool fill=true);
bool isClosedFigure(figure_t &figure);
void updateClosedFlag(figures_t &figures);

#endif // FILL_H
