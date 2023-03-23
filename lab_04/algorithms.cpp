#include "algorithms.h"

static void draw_pixcel(const int x, const int y, QColor color, QGraphicsScene *scene)
{
	QPen pen = QPen(color);
	pen.setJoinStyle(Qt::MiterJoin); // не съедаются углы у пикселей
	QBrush brush = QBrush(color);

	scene->addRect(x, y, 1, 1, pen, brush);
}

static void draw_pixcels_quarter(const int x, const int y, const int x0, const int y0, QColor color, QGraphicsScene *scene)
{
	draw_pixcel(x + x0, y + y0, color, scene);
	draw_pixcel(y + x0, x + y0, color, scene);
	draw_pixcel(-y + x0, x + y0, color, scene);
	draw_pixcel(-x + x0, y + y0, color, scene);
	draw_pixcel(-x + x0, -y + y0, color, scene);
	draw_pixcel(-y + x0, -x + y0, color, scene);
	draw_pixcel(y + x0, -x + y0, color, scene);
	draw_pixcel(x + x0, -y + y0, color, scene);
}

static void draw_pixcels_half(const int x, const int y, const int x0, const int y0, QColor color, QGraphicsScene *scene)
{
	draw_pixcel(x + x0, y + y0, color, scene);
	draw_pixcel(-x + x0, y + y0, color, scene);
	draw_pixcel(-x + x0, -y + y0, color, scene);
	draw_pixcel(x + x0, -y + y0, color, scene);
}

void lib_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	QRectF c = QRectF(circle.centerX - circle.r, circle.centerY + circle.r, circle.r * 2, circle.r * 2);
	if (draw) scene->addEllipse(c, QPen(circle.color), QBrush(QColor(0, 0, 0, 0)));
}

void lib_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw)
{
	QRectF el = QRectF(ellipse.centerX, ellipse.centerY, ellipse.a * 2, ellipse.b * 2);
	if (draw) scene->addEllipse(el, QPen(ellipse.color), QBrush(QColor(0, 0, 0, 0)));
}

void canonical_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	double x = 0;
	double y = 0;
	double r = circle.r;
	double rd = r * r;
	double rsq = r * sqrt(2) / 2;

	do {
		y = sqrt(rd - x * x);
		if (draw) draw_pixcels_quarter(x, y, circle.centerX, circle.centerY, circle.color, scene);
		x += 1;
	}
	while (x < rsq);
}

void canonical_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw)
{
	double x = 0;
	double y = 0;

	double a = ellipse.a;
	double b = ellipse.b;
	double db = b * b;
	double da = a * a;

	double asq = a * sqrt(2) / 2;
	double bsq = b * sqrt(2) / 2;

	do {
		y = sqrt(db - x * x * db / da);
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		x += 1;
	}
	while (x < asq);

	y = 0;
	do {
		x = sqrt(da - y * y * da / db);
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		y += 1;
	}
	while (y < bsq);
}

void parametric_algorithm(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	double angle = 0;
	double x = circle.r;
	double y = 0;
	double r = circle.r;

	double inc = 1 / r;
	angle += inc;

	if (draw) draw_pixcels_quarter(x, y, circle.centerX, circle.centerY, circle.color, scene);

	while (angle < M_PI_4)
	{
		x = r * cos(angle);
		y = r * sin(angle);
		angle += inc;

		if (draw) draw_pixcels_quarter(x, y, circle.centerX, circle.centerY, circle.color, scene);
	}
}

void parametric_algorithm(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw)
{
	double angle = 0;
	double x = ellipse.a;
	double y = 0;

	double a = ellipse.a;
	double b = ellipse.b;

	double inc = a > b ? 1 / a : 1 / b;
	angle += inc;

	if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);

	while (angle < M_PI_2)
	{
		x = a * cos(angle);
		y = b * sin(angle);
		angle += inc;

		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
	}
}

void bresenham_circle(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	int x = 0;
	int y = round(circle.r);

	int delta = 2 * (1 - circle.r);
	int err = 0;

	int sy = round(y * sqrt(2) / 2);

	do {
		if (draw) draw_pixcels_quarter(x, y, circle.centerX, circle.centerY, circle.color, scene);

		if (delta < 0)
		{
			err = 2 * delta + 2 * y - 1;
			if (err <= 0)
			{
				x += 1;
				delta += (2 * x + 1);
			}
			else
			{
				x += 1;
				y -= 1;
				delta += (2 * x - 2 * y + 2);
			}
		}
		else if (delta > 0)
		{
			err = 2 * delta + 2 * x - 1;
			if (err <= 0)
			{
				x += 1;
				y -= 1;
				delta += (2 * x - 2 * y + 2);
			}
			else
			{
				y -= 1;
				delta = delta - 2 * y + 1;
			}
		}
		else
		{
			x += 1;
			y -= 1;
			delta += (2 * x - 2 * y + 2);
		}
		continue;
	}
	while (y >= sy);
}

void bresenham_ellipse(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw)
{
	int x = 0;
	int y = round(ellipse.b);

	int sa = round(ellipse.a * ellipse.a);
	int sb = round(ellipse.b * ellipse.b);

	int delta = 4 * (x + 1) * (x + 1) * sb + sa * (2 * y - 1) * (2 * y - 1) - 4 * sa * sb;

	while (sa * (2 * y - 1) > 2 * sb * (x + 1))
	{
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		if (delta < 0) // горизонтальный шаг
		{
			x++;
			delta += 4 * sb * (2 * x + 3);
		}
		else // диаг шаг
		{
			x++;
			delta = delta - 8 * sa * (y - 1) + 4 * sb * (2 * x + 3);
			y--;
		}
	}

	delta = sb * ((2 * x + 1) * (2 * x + 1)) + 4 * sa * (y + 1) * (y + 1) - 4 * sa * sb;
	while (y + 1 != 0)
	{
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		if (delta < 0) // вертикаль
		{
			y--;
			delta += 4 * sa * (2 * y + 3);

		}
		else //диаг
		{
			y--;
			delta = delta - 8 * sb * (x + 1) + 4 * sa * (2 * y + 3);
			x++;
		}
	}
}

void middle_point(const ellipse_t &ellipse, QGraphicsScene *scene, bool draw)
{
	int x = 0;
	int y = round(ellipse.b);

	int a = round(ellipse.a);
	int b = round(ellipse.b);

	int sa = a * a;
	int sb = b * b;

	int dx = 2 * sb * x;
	int dy = 2 * sa * y;

	int f = 4 * sb + sa - sa * b;

	while (dx < dy)
	{
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		x++;
		dx += 2 * sb;

		if (f > 0)
		{
			y--;
			dy -= 2 * sa;
			f -= dy;
		}

		f += (sb + dx);
	}

	f = 4 * sa * y - 4 * sb * x + 3 * (sa - sb);
	while (y >= 0)
	{
		if (draw) draw_pixcels_half(x, y, ellipse.centerX, ellipse.centerY, ellipse.color, scene);
		y--;
		dy -= 2 * sa;

		if (f < 0)
		{
			x++;
			dx += 2 * sb;
			f += dx;
		}

		f += (sa - dy);
	}
}

void middle_point(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	int x = 0;
	int y = round(circle.r);
	int r = round(circle.r);

	int boundary = round(r * sqrt(2) / 2);

	int f = 1 - r;
	while (x <= boundary)
	{
		if (draw) draw_pixcels_quarter(x, y, circle.centerX, circle.centerY, circle.color, scene);
		x++;
		if (f < 0)
			f += 2 * x + 1;
		else
		{
			y--;
			f += 2 * (x - y) + 1;
		}
	}
}
