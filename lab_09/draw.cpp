#include "draw.h"

void drawPoint(Point p, QPainter *paint)
{
	paint->drawEllipse(p.getX() - 1, p.getY() - 1, COEF, COEF);
}

void drawLine(Line line, QPainter *paint)
{
	paint->drawLine(line.getStart().getX(), line.getStart().getY(), line.getFinish().getX(), line.getFinish().getY());
}

void drawFigure(figure_t &figure, QPainter *paint)
{
	size_t size_point = figure.points.size();
	if (size_point >= 2)
		for (size_t i = 0; i < size_point - 1; i++)
			drawLine(Line(figure.points[i], figure.points[i + 1]), paint);
	if (figure.isClose)
		drawLine(Line(figure.points[0], figure.points[size_point - 1]), paint);
}

void draw(figure_t &clipper, figure_t &figure, figure_t &resFigure, QPainter *painter, currentColors colors)
{
	painter->setBrush(colors.clipperColor);
	painter->setPen(colors.clipperColor);
	drawFigure(clipper, painter);

	painter->setBrush(colors.clipPolyColor);
	painter->setPen(colors.clipPolyColor);
	drawFigure(figure, painter);

	painter->setBrush(colors.resultColor);
	painter->setPen(colors.resultColor);
	drawFigure(resFigure, painter);
}


