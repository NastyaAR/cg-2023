#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QColor>
#include <QGraphicsScene>


struct circle
{
	double centerX;
	double centerY;
	double r;
	QColor color;
};

using circle_t = struct circle;

struct ellipse
{
	double centerX;
	double centerY;
	double a;
	double b;
	QColor color;
};

using ellipse_t = struct ellipse;

struct state
{
	std::vector <circle_t> circles;
	std::vector <ellipse_t> ellipses;
	QColor cur_color;
	QColor sceneColor;
};

using state_t = struct state;

void bresenham_circle(const circle_t &circle, QGraphicsScene *scene, bool draw=true);

#endif // ALGORITHMS_H
