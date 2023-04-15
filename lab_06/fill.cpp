#include "fill.h"

static void initEdge(edge_t &edge, double x, double dx, int dy)
{
	edge.xWithScanLine = x + 1;
	edge.dx = dx;
	edge.scanLineNumber = dy;
}

static void addEdgeToYGroup(line_segment_t &line, edges_t *yGroups)
{
	edge_t newEdge;

	double dy = (line.finishPoint.y - line.startPoint.y);
	double dx = (line.finishPoint.y - line.startPoint.y) != 0 ? (double)((-(line.finishPoint.x - line.startPoint.x)) / dy) : 0;
	if (dy != 0) {
	initEdge(newEdge, (double) line.finishPoint.x, dx, dy);
	yGroups[line.finishPoint.y].push_back(newEdge);
	}
}

static int getMaxScanLine(points_t &points)
{
	int max = points[0].y;
	for (size_t i = 0; i < points.size(); ++i)
		if (points[i].y > max)
			max = points[i].y;
	return max;
}

static int getMinScanLine(points_t &points)
{
	int min = points[0].y;
	for (size_t i = 0; i < points.size(); ++i)
		if (points[i].y < min)
			min = points[i].y;
	return min;
}

static int getMinX(points_t &points)
{
	int min = points[0].x;
	for (size_t i = 0; i < points.size(); ++i)
		if (points[i].x < min)
			min = points[i].x;
	return min;
}

static int getMaxX(points_t &points)
{
	int max = points[0].x;
	for (size_t i = 0; i < points.size(); ++i)
		if (points[i].x > max)
			max = points[i].x;
	return max;
}

static edges_t *allocateYGroups(int number)
{
	edges_t *YGroups = new edges_t[number];
	if (!YGroups)
		return NULL;

	return YGroups;
}

int makeYGroups(lines_t &lines, points_t &points, edges_t **yGroups)
{
	int number = getMaxScanLine(points) + 1;
	(*yGroups) = allocateYGroups(number);

	if (!(*yGroups))
		return 0;

	for (size_t i = 0; i < lines.size(); ++i)
		addEdgeToYGroup(lines[i], (*yGroups));

	return number;
}

static bool isEqualEdges(const edge_t &edge1, const edge_t &edge2)
{
	if (edge1.dx == edge2.dx && edge1.scanLineNumber == edge2.scanLineNumber && edge1.xWithScanLine == edge2.xWithScanLine)
		return true;
	return false;
}

static bool isEdgeInLAE(const edge_t &edge, edges_t &LAE)
{
	for (size_t i = 0; i < LAE.size(); ++i)
		if (isEqualEdges(edge, LAE[i]))
			return true;

	return false;
}

static bool compEdgeX(const edge_t &edge1, const edge_t &edge2)
{
	return edge1.xWithScanLine <= edge2.xWithScanLine;
}

static void decreaseLAE(edges_t &LAE)
{
	for (size_t i = 0; i < LAE.size(); ++i)
		--(LAE[i].scanLineNumber);
}

static void checkLAE(edges_t &LAE)
{
	for (auto el = LAE.begin(); el != LAE.end(); ++el)
		if (el->scanLineNumber < 1)
			LAE.erase(el--);
}

static void computeNewX(edges_t &LAE)
{
	for (size_t i = 0; i < LAE.size(); ++i)
		LAE[i].xWithScanLine += LAE[i].dx;
}

static void makeDelay(int sleep_time)
{
	QTime end = QTime::currentTime().addMSecs(sleep_time);
	while (QTime::currentTime() < end)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

void fillFigure(figure_t &figure, QImage *image, QGraphicsScene *scene, double delay, bool fill)
{
	edges_t listActiveEdges;

	edges_t *yGroups = NULL;
	int number = makeYGroups(figure.lines, figure.points, &yGroups);

	for (size_t i = number - 1; i > 0; --i)
	{
		for (size_t j = 0; j < yGroups[i].size(); ++j)
			if (!isEdgeInLAE(yGroups[i][j], listActiveEdges))
				listActiveEdges.push_back(yGroups[i][j]);

		std::sort(listActiveEdges.begin(), listActiveEdges.end(), compEdgeX);

		for (size_t j = 0; j < listActiveEdges.size(); j += 2) {
			if (delay != 0)
				makeDelay(delay);
			if (fill) drawStr((listActiveEdges[j].xWithScanLine), (listActiveEdges[j + 1].xWithScanLine), i, figure.fillColor, image);
		}

		if (fill) {
		scene->clear();
		QPixmap pixmap = QPixmap::fromImage(*image);
		QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
		item->update(); }

		decreaseLAE(listActiveEdges);
		checkLAE(listActiveEdges);
		computeNewX(listActiveEdges);
	}

	if (fill) drawCountour(figure.lines, image);
	delete[] yGroups;
}

int getIndexCurFigure(figures_t &figures, figure_t &hole)
{
	int yMin, yMax, xMin, xMax;

	for (size_t i = 0; i < figures.size(); ++i)
	{
		yMin = getMinScanLine(figures[i].points);
		yMax = getMaxScanLine(figures[i].points);
		xMin = getMinX(figures[i].points);
		xMax = getMaxX(figures[i].points);

		for (size_t i = 0; i < hole.points.size(); ++i)
			if (hole.points[i].y > yMax || hole.points[i].y < yMin || hole.points[i].x > xMax || hole.points[i].x < xMin)
				continue;
		return i;
	}

	return NOFITFIGURE;
}

void drawFigure(figure_t &figure, QImage *image, QGraphicsScene *scene, bool fill)
{
	drawCountour(figure.lines, image);
	if (figure.isClosed && fill)
		fillFigure(figure, image, scene);
}

void drawFigures(figures_t &figures, QImage *image, QGraphicsScene *scene, bool fill)
{
	for (size_t i = 0; i < figures.size(); ++i)
		drawFigure(figures[i], image, scene, fill);
}

bool isClosedFigure(figure_t &figure)
{
	for (size_t i = 0; i < figure.points.size(); ++i)
		if (countLinesContainPoint(figure.lines, figure.points[i]) < 2)
			return false;
	return true;
}

void updateClosedFlag(figures_t &figures)
{
	for (size_t i = 0; i < figures.size(); ++i)
		figures[i].isClosed = isClosedFigure(figures[i]);
}


void fillSeed(figure_t &figure, QGraphicsView *graphicsView, QImage *image, QGraphicsScene *scene, double delay, bool fill)
{
	std::stack <point_t> seedStack;
	seedStack.push(figure.seedPixel);

	while (! seedStack.empty())
	{
		point_t curPixel = seedStack.top();
		seedStack.pop();

		int x = curPixel.x;
		int y = curPixel.y;
		int tmpY = y;

		if (fill) draw_point(x, y, figure.fillColor, image);

		int tmpX = x;
		x = tmpX + 1;

		while (image->pixelColor(x, y) == Qt::transparent)
		{
			if (fill) draw_point(x, y, figure.fillColor, image);
			x++;
		}

		int rightX = x - 1;
		x = tmpX;
		x--;

		while (image->pixelColor(x, y) == Qt::transparent)
		{
			if (fill) draw_point(x, y, figure.fillColor, image);
			x--;
		}

		int leftX = x + 1;
		x = tmpX;

		x = leftX;
		y = tmpY - 1;

		while (x <= rightX)
		{
			bool flag = false;
			while ((image->pixelColor(x, y) != figure.borderColor
				   && image->pixelColor(x, y) != figure.fillColor)
				   && x < rightX)
			{
				if (flag == false) flag = true;
				x++;
			}

			if (flag)
			{
				if ((image->pixelColor(x, y) != figure.borderColor
						&& image->pixelColor(x, y) != figure.fillColor)
						&& x == rightX)
				{
					initPoint(curPixel, x, y);
					seedStack.push(curPixel);
				}
				else
				{
					initPoint(curPixel, x - 1, y);
					seedStack.push(curPixel);
				}
				flag = false;
			}

			int entryX = x;
			while ((image->pixelColor(x, y) == figure.borderColor
				   || image->pixelColor(x, y) == figure.fillColor)
				   && x < rightX)
				x++;

			if (x == entryX)
				x++;

		}

		x = leftX;
		y = tmpY + 1;

		while (x <= rightX)
		{
			bool flag = false;
			while (image->pixelColor(x, y) != figure.borderColor
				   && image->pixelColor(x, y) != figure.fillColor
				   && x < rightX)
			{
				if (flag == false) flag = true;
				x++;
			}

			if (flag)
			{
				if (image->pixelColor(x, y) != figure.borderColor
						&& image->pixelColor(x, y) != figure.fillColor
						&& x == rightX)
				{
					initPoint(curPixel, x, y);
					seedStack.push(curPixel);
				}
				else
				{
					initPoint(curPixel, x - 1, y);
					seedStack.push(curPixel);
				}
				flag = false;
			}

			int entryX = x;
			while ((image->pixelColor(x, y) == figure.borderColor
					|| image->pixelColor(x, y) == figure.fillColor)
					&& x < rightX)
				x++;

			if (x == entryX)
				x++;

		}
		if (delay)
		{
			makeDelay(delay);
		}
		if (fill) { scene->clear();
		QPixmap pixmap = QPixmap::fromImage(*image);
		QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
		item->update(); }
	}
}
