#include "joincommand.h"

joinCommand::joinCommand(int indexFigure, lines_t &joinLines, figures_t &figures, QGraphicsScene *scene, QUndoCommand *parent)
	: QUndoCommand(parent), scene(scene), indexFigure(indexFigure), figures(figures), joinLines(joinLines)
{
}

static bool isEqualPoints(point_t &point1, point_t &point2)
{
	if (point1.x != point2.x || point1.y != point2.y)
		return false;
	return true;
}

static bool isEqualLines(line_segment_t &line1, line_segment_t &line2)
{
	if (isEqualPoints(line1.finishPoint, line2.finishPoint) && isEqualPoints(line1.startPoint, line2.startPoint))
		return true;
	return false;
}

static void removeLineFromLines(lines_t &lines, line_segment_t &line)
{
	for (auto el = lines.begin(); el != lines.end(); ++el)
		if (isEqualLines(*el, line))
			lines.erase(el--);
}

void joinCommand::undo()
{
	scene->clear();
	QImage image = QImage(scene->width(), scene->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	for (size_t i = 0; i < joinLines.size(); ++i)
		removeLineFromLines(figures[indexFigure].lines, joinLines[i]);

	drawFigures(figures, &image, scene);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}
