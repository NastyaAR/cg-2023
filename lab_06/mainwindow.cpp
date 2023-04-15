#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene = new QGraphicsScene();

	ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft); // изначально сцена в верхнем левом углу
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setDragMode(QGraphicsView::NoDrag); // перетаскивание сцены по лкм (изначально отключено)
	ui->graphicsView->setRenderHint(QPainter::Antialiasing); // отключение сглаживания
	ui->graphicsView->setScene(scene);

	//undoStack = new QUndoStack(this);

	ui->graphicsView->viewport()->installEventFilter(this); // всё, что происходит в qgraphicsview отправляется в обработчик EventFilter

	QStringList horzHeaders;
	horzHeaders << "x" << "y";
	ui->tableWidget->setRowCount(1);
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setHorizontalHeaderLabels(horzHeaders);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет напрямую редактировать ячейки таблицы

	ui->label_2->setStyleSheet("background-color: green");
	ui->label_3->setStyleSheet("background-color: black");

	curColors.fillColor = Qt::green;
	curColors.borderColor = Qt::black;
}

MainWindow::~MainWindow()
{
	delete ui;
}


static point_t getSeedPoint(QLineEdit *lineX, QLineEdit *lineY)
{
	point_t seedPoint;
	initPoint(seedPoint, lineX->text().toInt(), lineY->text().toInt());
	return seedPoint;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	if (ui->comboBox->currentIndex() == SCALE_MODE)
	{
		ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		if (event->angleDelta().y() > 0)
			ui->graphicsView->scale(SCALE, SCALE);
		else
			ui->graphicsView->scale(1 / SCALE, 1 / SCALE);

		ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	}
}


static void update_color_on_label(QLabel *label, QColor color)
{
	QPixmap pixmap = QPixmap(label->width(), label->height());
	QPainter *painter = new QPainter(&pixmap);
	QBrush *brush = new QBrush(color);

	painter->setPen(color);
	painter->fillRect(0, 0, pixmap.width(), pixmap.height(), *brush);

	label->clear();
	label->setPixmap(pixmap);

	delete painter;
	delete brush;
}

static void updateColorOfFigures(figures_t &figures, QColor fill, QColor border)
{
	for (size_t i = 0; i < figures.size(); ++i)
	{
		//initFigure(figures[i], figures[i].lines, figures[i].points, fill, border, figures[i].isClosed, figures[i].holes);
		//updateLinesColor(figures[i].lines, border);
	}
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	if (index == VIEW_MODE)
		ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	else
		ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}


void MainWindow::on_pushButton_clicked()
{
	curColors.fillColor = QColorDialog::getColor();
	update_color_on_label(ui->label_2, curColors.fillColor);
	updateColorOfFigures(figures, curColors.fillColor, curColors.borderColor);
	//updateLinesColor(lines, curColors.borderColor);
}

void MainWindow::on_pushButton_2_clicked()
{
	curColors.borderColor = QColorDialog::getColor();
	update_color_on_label(ui->label_3, curColors.borderColor);
	updateColorOfFigures(figures, curColors.fillColor, curColors.borderColor);
	//updateLinesColor(lines, curColors.borderColor);
}


void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (ui->comboBox->currentIndex() == INPUT_MODE) {
	QRect view = ui->graphicsView->geometry();

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	point_t p;
	line_segment_t line;

	if (view.contains(event->pos())) {
		initPoint(p, event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height());
		points.push_back(p);
		addPointOnClick(ui->tableWidget, p);
		draw_point(p, curColors.borderColor, &image);
	}

	if (points.size() > 1 && flag) {
		initLine(line, points[points.size() - 1], points[points.size() - 2], curColors.borderColor);
		drawLine(line, &image);
		lines.push_back(line);
	}

	if (flag == false) flag = true;

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
	}
}

void MainWindow::on_pushButton_3_clicked()
{
	bool ok1, ok2;

	int x = QInputDialog::getInt(0, "Введите x: ", "x = ", 0, INT_MIN, INT_MAX, 1, &ok1);
	int y = QInputDialog::getInt(0, "Введите y: ", "y = ", 0, INT_MIN, INT_MAX, 1, &ok2);

	if (!ok1 || !ok2)
	{
		printf("error\n");
		return;
	}

	point_t point;
	initPoint(point, x, y);

	points.push_back(point);

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	draw_point(point, curColors.borderColor, &image);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);

	addPointOnClick(ui->tableWidget, point);
}


void MainWindow::on_pushButton_10_clicked()
{
	scene->clear();
	figures.clear();
	lines.clear();
	points.clear();
	flag = true;
	addHole = false;
	clearTable(ui->tableWidget);
}


void MainWindow::on_pushButton_4_clicked()
{
	scene->clear();

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	point_t remPoint = removePointFromTable(ui->tableWidget);
	removePointFromScene(remPoint, &image);

	removePointFromFigure(figures, remPoint);

	updateClosedFlag(figures);

	drawFigures(figures, &image, scene);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}


void MainWindow::on_pushButton_11_clicked()
{
	ui->graphicsView->resetTransform();
}


static lines_t getJoinLines(const points_t &points, const QColor color)
{
	lines_t joinLines;
	line_segment_t line;

	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		initLine(line, points[i], points[i + 1], color);
		joinLines.push_back(line);
	}

	return joinLines;
}

static points_t getSelectesPoints(QList <QTableWidgetItem *> list, QTableWidget *tableWidget)
{
	points_t selectedPoints;
	point_t point;

	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i]->column())
			initPoint(point, tableWidget->item(list[i]->row(), 0)->text().toInt(), list[i]->text().toInt());
		else
			initPoint(point, list[i]->text().toInt(), tableWidget->item(list[i]->row(), 1)->text().toInt());
		selectedPoints.push_back(point);
	}

	return selectedPoints;
}

static void addJoinLinesToLines(lines_t &joinLines, lines_t &linesTo)
{
	for (size_t i = 0; i < joinLines.size(); ++i)
		linesTo.push_back(joinLines[i]);
}

void MainWindow::on_pushButton_5_clicked()
{
	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QList <QTableWidgetItem *> list = ui->tableWidget->selectedItems();

	points_t selectedPoints = getSelectesPoints(list, ui->tableWidget);
	lines_t joinLines = getJoinLines(selectedPoints, curColors.borderColor);

	int i = getFigureFromPoints(figures, selectedPoints);

	figure_t newFigure;
	figures_t holes;

	point_t seedPoint = getSeedPoint(ui->lineEdit, ui->lineEdit_2);

	if (figures.size() != 0)
		addJoinLinesToLines(joinLines, figures[i].lines);
	else {
		addJoinLinesToLines(joinLines, lines);
		initFigure(newFigure, lines, points, curColors.fillColor, curColors.borderColor, true, holes, seedPoint);
		figures.push_back(newFigure);
	}

	drawCountour(joinLines, &image);

	//QUndoCommand *joinCmd = new joinCommand(i, joinLines, figures, scene);
	//undoStack->push(joinCmd);

	updateClosedFlag(figures);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}


template<typename T>
std::vector<T> create_copy(std::vector<T> const &vec)
{
	std::vector<T> v;
	v.insert(v.begin(), vec.begin(), vec.end());

	return v;
}

template<typename  T>
void addVec(std::vector<T> &src, std::vector<T> &dest)
{
	for (size_t i = 0; i < src.size(); ++i)
		dest.push_back(src[i]);
}

void MainWindow::on_pushButton_6_clicked()
{
	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	line_segment_t line;

	initLine(line, points[0], points[points.size() - 1], curColors.borderColor);
	drawLine(line, &image);

	lines.push_back(line);

	lines_t copyLines = create_copy(lines);
	points_t copyPoints = create_copy(points);

	figure_t newFigure;
	figures_t holes;
	point_t seedPoint = getSeedPoint(ui->lineEdit, ui->lineEdit_2);
printf("in %d %d\n", seedPoint.x, seedPoint.y);
	initFigure(newFigure, copyLines, copyPoints, curColors.fillColor, curColors.borderColor, true, holes, seedPoint);
	if (!addHole) {
		figures.push_back(newFigure);
	}
	else {
		int i = getIndexCurFigure(figures, newFigure);
		if (i != NOFITFIGURE) {
			addVec(newFigure.points, figures[i].points);
			addVec(newFigure.lines, figures[i].lines);
		}
		figures[i].holes.push_back(newFigure);
		addHole = false;
	}

	//QUndoCommand *clsCmd = new closeCommand(figures.size() - 1, line, figures, scene);
	//undoStack->push(clsCmd);

	points.clear();
	lines.clear();

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}


void MainWindow::on_pushButton_7_clicked()
{
	addHole = true;
}


void MainWindow::on_pushButton_8_clicked()
{
	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	drawCountour(figures[0].lines, &image);

	printf("%d %d\n", figures[0].seedPixel.x, figures[0].seedPixel.y);
	fillSeed(figures, ui->graphicsView, scene, 5);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->addPixmap(pixmap);
}

