#include "draw.h"

#define C 2

void draw_point(const point_t &point, const QColor color, QImage *image)
{
	image->setPixelColor(point.x, point.y - C/2, color);
}

static int sign(const double x)
{
	if (x < 0)
		return -1;
	else if (x > 0)
		return 1;

	return 0;
}

void swapPoints(line_segment_t &line)
{
	int tmp;

	if (line.startPoint.y > line.finishPoint.y)
	{
		tmp = line.startPoint.x;
		line.startPoint.x = line.finishPoint.x;
		line.finishPoint.x = tmp;
		tmp = line.startPoint.y;
		line.startPoint.y = line.finishPoint.y;
		line.finishPoint.y = tmp;
	}
}


static void dda_algorithm(const line_segment_t &line, QImage *image)
{
	double len;

	if (fabs(line.finishPoint.x - line.startPoint.x) >= fabs(line.finishPoint.y - line.startPoint.y))
		len = fabs(line.finishPoint.x - line.startPoint.x);
	else
		len = fabs(line.finishPoint.y - line.startPoint.y);

	double dx = (line.finishPoint.x - line.startPoint.x) / len;
	double dy = (line.finishPoint.y - line.startPoint.y) / len;

	double x = line.startPoint.x + 0.5 * sign(dx);
	double y = line.startPoint.y + 0.5 * sign(dy);

	int cx = qRound(x);
	int cy = qRound(y);

	point_t cur_point;
	initPoint(cur_point, cx, cy);

	int i = 0;
	while (i <= len)
	{
		draw_point(cur_point, line.color, image);
		x = x + dx;
		y = y + dy;
		initPoint(cur_point, qRound(x), qRound(y));
		i++;
	}
}


void drawLine(const line_segment_t &line, QImage *image)
{
	dda_algorithm(line, image);
}

void removePointFromScene(const point_t &point, QImage *image)
{
	image->setPixelColor(point.x, point.y, Qt::white);
}

void drawStr(const int x1, const int x2, const int y, const QColor color, QImage *image)
{
	point_t point;
	initPoint(point, x1, y);

	if (x1 == x2) {
		draw_point(point, color, image);
		return;
	}


	for (int i = x1 + 1; i <= x2; ++i)
	{
		draw_point(point, color, image);
		initPoint(point, i, y);
	}
}

void drawCountour(lines_t &lines, QImage *image)
{
	for (size_t i = 0; i < lines.size(); ++i)
		drawLine(lines[i], image);
}

void initPoint(point_t &point, const int x, const int y)
{
	point.x = x;
	point.y = y;
}

void initLine(line_segment_t &line, const point_t start, const point_t finish, const QColor color)
{
	line.startPoint = start;
	line.finishPoint = finish;
	line.color = color;

	if (line.startPoint.y > line.finishPoint.y) swapPoints(line);
}

void initFigure(figure_t &figure, const lines_t lines, const points_t points, const QColor fill,
				const QColor border, bool isClosed, const figures_t holes)
{
	figure.lines = lines;
	figure.points = points;
	figure.fillColor = fill;
	figure.borderColor = border;
	figure.isClosed = isClosed;
	figure.holes = holes;
}

void updateLinesColor(lines_t &lines, QColor color)
{
	for (size_t i = 0; i < lines.size(); ++i)
		lines[i].color = color;
}

static bool isEqualPoints(point_t &point1, point_t &point2)
{
	if (point1.x != point2.x || point1.y != point2.y)
		return false;
	return true;
}

static bool isPointInLine(line_segment_t &line, point_t &point)
{
	printf("line s %d %d f %d %d p %d %d\n", line.startPoint.x, line.startPoint.y, line.finishPoint.x, line.finishPoint.y, point.x, point.y);
	if (isEqualPoints(line.startPoint, point) || isEqualPoints(line.finishPoint, point))
		return true;
	return false;
}

static void removePointFromPoints(points_t &points, point_t &remPoint)
{
	for (auto el = points.begin(); el != points.end(); ++el)
		if (isEqualPoints(*el, remPoint))
			points.erase(el--);
}

static void removeLineFromLines(lines_t &lines, point_t &remPoint)
{
	for (auto el = lines.begin(); el != lines.end(); ++el)
		if (isPointInLine(*el, remPoint))
			lines.erase(el--);
}

void removePointFromFigure(figures_t &figures, point_t &remPoint)
{
	for (size_t i = 0; i < figures.size(); ++i) {
		removePointFromPoints(figures[i].points, remPoint);
		removeLineFromLines(figures[i].lines, remPoint);
		figures[i].isClosed = false;
	}
}

