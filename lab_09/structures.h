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

enum whatInput {
	CLIPPER,
	FIGURE,
};

struct currentColors {
	QColor clipperColor;
	QColor clipPolyColor;
	QColor resultColor;
};

using currentColors_t = struct currentColors;

class Point {
public:
	Point() {};
	Point(int xValue, int yValue) { x = xValue; y = yValue; };

	bool operator==(Point &point) const { return (this->x == point.x) && (this->y == point.y); };
	bool operator!=(Point &point) const { return !(*this == point); };

	Point operator-(Point p) const { return Point(x - p.x, y - p.y); };
	Point operator+(Point p) const { return Point(x + p.x, y + p.y); };

	int getX() { return this->x; };
	int getY() { return this->y; };

	void setX(int newX) { x = newX; };
	void setY(int newY) { y = newY; };
private:
	int x = 0;
	int y = 0;
};

class Line {
public:
	Line(Point &startValue, Point &finishValue) { start = startValue; finish = finishValue; };

	Point getStart() { return this->start; };
	Point getFinish() { return this->finish; };

private:
	Point start;
	Point finish;
};

using points_t = std::vector <Point>;
using lines_t = std::vector <Line>;

struct figure
{
	points_t points;
	lines_t lines;
	bool isClose;
	QColor color;
};

using figure_t = struct figure;

#endif // STRUCTURES_H
