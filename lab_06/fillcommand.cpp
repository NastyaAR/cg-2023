#include "fillcommand.h"

fillCommand::fillCommand(figures_t figures, QGraphicsScene *scene, QUndoCommand *parent)
	: QUndoCommand(parent), scene(scene), figures(figures)
{
}

void fillCommand::undo()
{
	scene->clear();
	QImage image = QImage(scene->width(), scene->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	drawFigures(figures, &image, scene, false);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}
