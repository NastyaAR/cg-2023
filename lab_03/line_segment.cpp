#include "line_segment.h"

static int sign(const double x)
{
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;

    return 0;
}

static void draw_pixcel(const int x, const int y, QColor color, QGraphicsScene *scene)
{
    QPen pen = QPen(color);
    QBrush brush = QBrush(color);

    scene->addRect(x, y, 1, 1, pen, brush);
}

void lib_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
	QLineF line_obj = QLineF(line.start_x, line.start_y, line.finish_x, line.finish_y);
	if (draw) scene->addLine(line_obj, QPen(line.color));
}

void dda_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
    double len;

    if (fabs(line.finish_x - line.start_x) >= fabs(line.finish_y - line.start_y))
        len = fabs(line.finish_x - line.start_x);
    else
        len = fabs(line.finish_y - line.start_y);

    double dx = (line.finish_x - line.start_x) / len;
    double dy = (line.finish_y - line.start_y) / len;

    double x = line.start_x + 0.5 * sign(dx);
    double y = line.start_y + 0.5 * sign(dy);

	double old_x = x;
	double old_y = y;

    int i = 0;
    while (i <= len)
    {
		if (draw) draw_pixcel(round(x), round(y), line.color, scene);
        x = x + dx;
        y = y + dy;

		if (step_number)
		{
			if (round(x) != round(old_x) && round(y) != round(old_y))
				(*step_number)++;
			old_x = x;
			old_y = y;
		}
        i++;
    }
}

void double_bresenham_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
	double x = line.start_x;
	double y = line.start_y;

	double dx = fabs(line.finish_x - line.start_x);
	double dy = fabs(line.finish_y - line.start_y);

	int s1 = sign(line.finish_x - line.start_x);
	int s2 = sign(line.finish_y - line.start_y);

	bool change = false;

	if (dy > dx)
	{
		double t = dx;
		dx = dy;
		dy = t;
		change = true;
	}
	else
		change = false;

	double m = dy / dx;

	double old_x = x;
	double old_y = y;

	double e = m - 0.5;
	for (int i = 1; i < dx; i++)
	{
		if (draw) draw_pixcel(x, y, line.color, scene);
		while (e >= 0)
		{
			if (change)
				x += s1;
			else
				y += s2;
			e--;
		}
		e += m;
		if (change)
			y += s2;
		else
			x += s1;

		if (step_number)
		{
			if (round(x) != round(old_x) && round(y) != round(old_y))
				(*step_number)++;
			old_x = x;
			old_y = y;
		}
	}
}

void int_bresenham_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
	int x = round(line.start_x);
	int xn = round(line.finish_x);
	int y = round(line.start_y);
	int yn = round(line.finish_y);

	int dx = abs(xn - x);
	int dy = abs(yn - y);

	int s1 = sign(xn - x);
	int s2 = sign(yn - y);

	bool change = false;

	if (dy > dx)
	{
		int t = dx;
		dx = dy;
		dy = t;
		change = true;
	}
	else
		change = false;

	int e = 2 * dy - dx;

	int old_x = x;
	int old_y = y;

	for (int i = 1; i < dx; i++)
	{
		if (draw) draw_pixcel(x, y, line.color, scene);
		while (e >= 0)
		{
			if (change)
				x += s1;
			else
				y += s2;
			e -= (2 * dx);
		}
		e += (2 * dy);
		if (change)
			y += s2;
		else
			x += s1;
		if (step_number)
		{
			if (round(x) != round(old_x) && round(y) != round(old_y))
				(*step_number)++;
			old_x = x;
			old_y = y;
		}
	}
}

static void intensity_regulation(QColor &color, double intensity)
{
	int res = 255 * intensity;

	if (res > 255)
		res = 255;
	if (res < 0)
		res = 0;

	color = QColor(color.red(), color.green(), color.blue(), res);
}

void bresenham_without_gradation(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
	double x = line.start_x;
	double y = line.start_y;

	double dx = fabs(line.finish_x - line.start_x);
	double dy = fabs(line.finish_y - line.start_y);

	int s1 = sign(line.finish_x - line.start_x);
	int s2 = sign(line.finish_y - line.start_y);

	bool change = false;

	if (dy > dx)
	{
		double t = dx;
		dx = dy;
		dy = t;
		change = true;
	}
	else
		change = false;

	double m = dy / dx;

	double e = 0.5;
	double w = 1 - m;
	QColor new_color = line.color;
	intensity_regulation(new_color, e);

	double old_x = x;
	double old_y = y;

	if (draw) draw_pixcel(x, y, new_color, scene);

	for (int i = 1; i < dx; i++)
	{
		if (e < w)
		{
			if (change)
				y += s2;
			else
				x += s1;
			e += m;
		}
		else
		{
			x += s1;
			y += s2;
			e -= w;
		}

		intensity_regulation(new_color, e);
		if (draw) draw_pixcel(x, y, new_color, scene);
		if (step_number)
		{
			if (x != old_x && y != old_y)
				(*step_number)++;
			old_x = x;
			old_y = y;
		}
	}
}

static void my_swap(double &el1, double &el2)
{
	double t = el1;
	el1 = el2;
	el2 = t;
}

static double fpart(double x)
{
	return x - int(x);
}

static double ipart(double x)
{
	return x - fpart(x);
}

static double mround(double x)
{
	return ipart(x + 0.5);
}

void wu_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number)
{
	QColor c1 = line.color;
	QColor c2 = line.color;

	double x1 = line.start_x;
	double xn = line.finish_x;
	double y1 = line.start_y;
	double yn = line.finish_y;

	bool change = false;

	if (fabs(line.finish_y - line.start_y) > fabs(line.finish_x - line.start_x))
	{
		my_swap(x1, y1);
		my_swap(xn, yn);
		change = true;
	}

	if (xn < x1)
	{
		my_swap(x1, xn);
		my_swap(y1, yn);
	}

	double dx = xn - x1;
	double dy = yn - y1;
	double m = (dx == 0) ? 1 : dy / dx;

	int xend = mround(x1);
	double yend = y1 + m * (xend - x1);
	double xgap = 1 - fpart(x1 + 0.5);

	int xpxl1 = xend;
	int ypxl1 = ipart(yend);

	intensity_regulation(c1, 1 - fpart(yend) * xgap);
	intensity_regulation(c2, fpart(yend) * xgap);

	if (! change)
	{
		if (draw) draw_pixcel(xpxl1, ypxl1, c1, scene);
		if (draw) draw_pixcel(xpxl1, ypxl1 + 1, c2, scene);
	}
	else
	{
		if (draw) draw_pixcel(ypxl1, xpxl1, c1, scene);
		if (draw) draw_pixcel(ypxl1 + 1, xpxl1, c2, scene);
	}

	double intery = yend + m;
	xend = mround(xn);
	yend = yn + m * (xend - xn);
	xgap = fpart(xn + 0.5);

	int xpxl2 = xend;
	int ypxl2 = ipart(yend);

	intensity_regulation(c1, 1 - fpart(yend) * xgap);
	intensity_regulation(c2, fpart(yend) * xgap);

	if (! change)
	{
		if (draw) draw_pixcel(xpxl2, ypxl2, c1, scene);
		if (draw) draw_pixcel(xpxl2, ypxl2 + 1, c2, scene);
	}
	else
	{
		if (draw) draw_pixcel(ypxl2, xpxl2, c1, scene);
		if (draw) draw_pixcel(ypxl2 + 1, xpxl2, c2, scene);
	}

	for (int xi = xpxl1 + 1; xi < xpxl2; xi++)
	{
		intensity_regulation(c1, 1 - fpart(intery) * xgap);
		intensity_regulation(c2, fpart(intery) * xgap);

		if (! change)
		{
			if (draw) draw_pixcel(xi, ipart(intery), c1, scene);
			if (draw) draw_pixcel(xi, ipart(intery) + 1, c2, scene);
		}
		else
		{
			if (draw) draw_pixcel(ipart(intery), xi, c1, scene);
			if (draw) draw_pixcel(ipart(intery) + 1, xi, c2, scene);
		}

		if (step_number && xi < xpxl2)
			if (ipart(intery) != ipart(intery + m))
				(*step_number)++;

		intery += m;
	}
}


