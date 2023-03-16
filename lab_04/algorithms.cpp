#include "algorithms.h"

static void draw_pixcel(const int x, const int y, QColor color, QGraphicsScene *scene)
{
	QPen pen = QPen(color);
	QBrush brush = QBrush(color);

	scene->addRect(x, y, 1, 1, pen, brush);
}

static void draw_pixcels(const int x, const int y, const int x0, const int y0, QColor color, QGraphicsScene *scene)
{
	draw_pixcel(x + x0, y + y0, color, scene);
	draw_pixcel(x0 - x, y + y0, color, scene);
	draw_pixcel(x + x0, y0 - y, color, scene);
	draw_pixcel(x0 - x, y0 - y, color, scene);
}

void bresenham_circle(const circle_t &circle, QGraphicsScene *scene, bool draw)
{
	double x = 0;
	double y = circle.r;

	double delta = 2 * (1 - circle.r);
	double err = 0;

	do {
		draw_pixcels(x, y, circle.centerX, circle.centerY, circle.color, scene);

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
	while (y > 0);
}


