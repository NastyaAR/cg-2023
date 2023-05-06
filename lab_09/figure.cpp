#include "figure.h"

static int vectorProduct(Point v1, Point v2)
{
	return v1.getX() * v2.getY() - v1.getY() * v2.getX();
}

static Point getVector(Line l)
{
	return Point(l.getFinish().getX() - l.getStart().getX(), l.getFinish().getY() - l.getStart().getY());
}

int sign(int n)
{
	if (n == 0)
		return 0;
	else if (n > 0)
		return 1;
	else
		return -1;
}

int isConvex(figure_t &cut)
{
	size_t size = cut.points.size();
	if (size < 3)
		return false;

	Point v1 = getVector(cut.lines[cut.lines.size() - 1]);
	Point v2 = getVector(cut.lines[0]);

	int sign1 = sign(vectorProduct(v1, v2));
	bool wasPlus = false;
	bool wasMinus = false;

	if (sign1 == 1)
		wasPlus = true;
	else if (sign1 == -1)
		wasMinus = true;

	for (size_t i = 0; i < cut.lines.size() - 1; i++)
	{
		v1 = getVector(cut.lines[i]);
		v2 = getVector(cut.lines[i + 1]);

		sign1 = sign(vectorProduct(v1, v2));
		if (sign1 == 1)
			wasPlus = true;
		else if (sign1 == -1)
			wasMinus = true;
	}

	if (wasPlus && wasMinus)
		return false;
	if (! wasPlus && ! wasMinus)
		return false;
	return true;
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

void addPointInFigure(figure_t &figure, Point point)
{
	figure.points.push_back(point);
}

void addLineInFigure(figure_t &figure, Line line)
{
	figure.lines.push_back(line);
}

void resetFigure(figure_t &figure)
{
	figure.points.clear();
	figure.lines.clear();
	figure.isClose = false;
}

void getLines(lines_t &lines, points_t &points)
{
	for (size_t i = 0; i < points.size() - 1; ++i)
		lines.push_back(Line(points[i], points[i + 1]));
	lines.push_back(Line(points[points.size() - 1], points[0]));
}

void addPointInList(QListWidget *list, Point p)
{
	char *src = new char(LEN);
	snprintf(src,LEN, "x=%d  y=%d", p.getX(), p.getY());
	list->addItem(QString(src));
	delete src;
}
