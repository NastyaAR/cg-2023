#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QColorDialog>
#include <QGraphicsScene>
#include <QPixmap>

enum modes {
	INPUT_MODE,
	SCALE_MODE,
	VIEW_MODE,
};

struct point {
	int x;
	int y;
};

using point_t = struct point;

struct line_segment
{
	point_t startPoint;
	point_t finishPoint;
	QColor color;
};

using line_segment_t = struct line_segment;

struct currentColors {
	QColor fillColor;
	QColor borderColor;
};

using lines_t = std::vector <line_segment_t>;
using points_t = std::vector <point_t>;

struct figure {
	points_t points;
	lines_t lines;
	std::vector <struct figure> holes;
	QColor borderColor;
	QColor fillColor;
	bool isClosed;
};

using figure_t = struct figure;

using figures_t = std::vector <figure_t>;

using currentColors_t = struct currentColors;

#endif // STRUCTURES_H
