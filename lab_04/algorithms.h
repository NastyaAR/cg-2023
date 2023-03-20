#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QColor>
#include <QGraphicsScene>
#include <QPen>
#include <math.h>

enum method_t
{
	CANONICAL,
	PARAMETRIC,
	STANDART,
	BRESENHAM,
	MIDDLE_POINT,
};

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

void lib_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw=true);
void lib_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw=true);
void canonical_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw=true);
void canonical_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw=true);
void parametric_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw=true);
void parametric_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw=true);
void bresenham_circle(const circle_t &circle, QGraphicsScene *scene, bool draw=true);
void bresenham_ellipse(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw=true);

#endif // ALGORITHMS_H
