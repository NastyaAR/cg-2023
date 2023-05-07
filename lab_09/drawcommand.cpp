#include "drawcommand.h"

drawCommand::drawCommand(figure_t srcFigure, figure_t clipper, currentColors_t colors, QGraphicsScene *scene, QListWidget *list1, QListWidget *list2, QUndoCommand *parent)
	: QUndoCommand(parent), scene(scene), clipper(clipper), srcFigure(srcFigure), c(colors), list1(list1), list2(list2)
{
}

static void updateList(QListWidget *list, char str[LEN], points_t &points)
{
	list->clear();
	list->insertItem(0, QString(str));
	for (size_t i = 0; i < points.size(); ++i)
		addPointInList(list, points[i]);
}


void drawCommand::undo()
{
	scene->clear();
	QImage image = QImage(scene->width(), scene->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);

	points_t points;
	lines_t lines;
	figure_t destFigure = {points, lines, false, Qt::black};
	draw(clipper, srcFigure, destFigure, &painter, c);

	updateList(list1, "Отсекатель", clipper.points);
	updateList(list2, "Многоугольник", srcFigure.points);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}
