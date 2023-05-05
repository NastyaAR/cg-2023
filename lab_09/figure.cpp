#include "figure.h"

int vectorProduct(Point v1, Point v2)
{
	return v1.getX() * v2.getY() - v1.getY() * v2.getX();
}

bool isConvex(figure_t &figure)
{
	for (size_t i = 0; i < figure.lines.size() - 1; i++)
	{
		Point p1 = figure.lines[i].getStart();
		Point p2 = figure.lines[i].getFinish();
		for (size_t j = i + 1; j < figure.lines.size(); j++) {
			Point p3 = figure.lines[j].getStart();
			Point p4 = figure.lines[j].getFinish();

			int v1 = vectorProduct(p3 - p4, p3 - p1);
			int v2 = vectorProduct(p3 - p4, p3 - p2);
			int v3 = vectorProduct(p1 - p2, p1 - p3);
			int v4 = vectorProduct(p1 - p2, p1 - p4);
			if (v1 > 0 && v2 < 0)
				return true;
			if (v1 < 0 && v2 > 0)
				return true;
			if (v3 > 0 && v4 < 0)
				return true;
			if (v3 < 0 && v4 > 0)
				return true;
		}
	}
	return false;
}

void initFigure(figure_t &figure, points_t &points, lines_t &lines, QColor color, bool isClose)
{
	figure.points = points;
	figure.lines = lines;
	figure.color = color;
	figure.isClose = isClose;
}

void initFigure(figure_t &figure, QColor color, bool isClose)
{
	figure.color = color;
	figure.isClose = isClose;
}

void addPointInFigure(figure_t)
