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

	undoStack = new QUndoStack(this);

	ui->graphicsView->viewport()->installEventFilter(this); // всё, что происходит в qgraphicsview отправляется в обработчик EventFilter

	ui->label_2->setStyleSheet("background-color: lightgreen");
	ui->label_3->setStyleSheet("background-color: pink");
	ui->label_4->setStyleSheet("background-color: black");

	curColors.clipperColor = QColor("#90EE90");
	curColors.clipPolyColor = QColor("#FFC0CB");
	curColors.resultColor = QColor(Qt::black);

	QAction *about_act = ui->menubar->addAction("О программе");
	connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
	QAction *about_me_act = ui->menubar->addAction("Об авторе");
	connect(about_me_act, SIGNAL(triggered()), this, SLOT(about_me()));

	initFigure(clipper, curColors.clipperColor, false);
	initFigure(srcFigure, curColors.clipPolyColor, false);
	initFigure(destFigure, curColors.resultColor, false);

	ui->listWidget->insertItem(0, QString("Отсекатель"));
	ui->listWidget_2->insertItem(0, QString("Многоугольник"));
}

void MainWindow::about()
{
	QMessageBox::information(this, "О программе", "Программа позволяет заполнить область затравочным алгоритмом заполения по строкам.\nРеализована возможность сравнения по времени алгоритмов с уп. списком рёбер (и САР) и затравочного.");
}

void MainWindow::about_me()
{
	QMessageBox::information(this, "Об авторе", "Алькина Анастасия ИУ7-44Б МГТУ им. Н.Э.Баумана");
}

MainWindow::~MainWindow()
{
	delete ui;
	delete undoStack;
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


void MainWindow::on_pushButton_clicked()
{
	curColors.clipperColor = QColorDialog::getColor();
	update_color_on_label(ui->label_2, curColors.clipperColor);
}


void MainWindow::on_pushButton_2_clicked()
{
	curColors.clipPolyColor = QColorDialog::getColor();
	update_color_on_label(ui->label_3, curColors.clipPolyColor);
}


void MainWindow::on_pushButton_3_clicked()
{
	curColors.resultColor = QColorDialog::getColor();
	update_color_on_label(ui->label_4, curColors.resultColor);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	if (ui->comboBox_2->currentIndex() == SCALE_MODE)
	{
		ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		if (event->angleDelta().y() > 0)
			ui->graphicsView->scale(SCALE, SCALE);
		else
			ui->graphicsView->scale(1 / SCALE, 1 / SCALE);

		ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	}
}

template <typename T>
void copyVector(T &v1, T &v2)
{
	for (size_t i = 0; i < v2.size(); ++i)
		v1.push_back(v2[i]);
}

void MainWindow::on_pushButton_9_clicked()
{
	points_t tmp;
	copyVector(tmp, srcFigure.points);
	clipper.points.push_back(clipper.points[0]);
	points_t destPoints = clip(tmp, clipper);
	lines_t destLines;
	getLines(destLines, destPoints);

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);
	painter.setBrush(curColors.resultColor);
	painter.setPen(curColors.resultColor);

	initFigure(destFigure, destPoints, destLines, curColors.resultColor, true);

	draw(clipper, srcFigure, destFigure, &painter, curColors);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->clear();
	scene->addPixmap(pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (ui->comboBox_2->currentIndex() == INPUT_MODE)
	{
		QRect view = ui->graphicsView->geometry();
		QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
		image.fill(Qt::transparent);
		QPainter painter(&image);
		painter.setBrush(curColors.clipperColor);
		painter.setPen(curColors.clipperColor);

		if (view.contains(event->pos())) {
			Point p(event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height());
			if (ui->comboBox->currentIndex() == CLIPPER) {
				QUndoCommand *drawCmd = new drawCommand(srcFigure, clipper, curColors, scene, ui->listWidget, ui->listWidget_2);
				undoStack->push(drawCmd);
				addPointInFigure(clipper, p);
				addPointInList(ui->listWidget, p);
				if (clipper.points.size() > 1)
					addLineInFigure(clipper, Line(clipper.points[clipper.points.size() - 2], p));
			}
			else if (ui->comboBox->currentIndex() == FIGURE) {
				QUndoCommand *drawCmd = new drawCommand(srcFigure, clipper, curColors, scene, ui->listWidget, ui->listWidget_2);
				undoStack->push(drawCmd);
				addPointInFigure(srcFigure, p);
				addPointInList(ui->listWidget_2, p);
				if (srcFigure.points.size() > 1)
					addLineInFigure(srcFigure, Line(srcFigure.points[srcFigure.points.size() - 2], p));
			}
		}

		drawFigure(clipper, &painter);

		painter.setBrush(curColors.clipPolyColor);
		painter.setPen(curColors.clipPolyColor);
		drawFigure(srcFigure, &painter);

		QPixmap pixmap = QPixmap::fromImage(image);
		scene->clear();
		scene->addPixmap(pixmap);
	}
}


void MainWindow::on_pushButton_6_clicked()
{
	ui->graphicsView->resetTransform();
}


void MainWindow::on_pushButton_5_clicked()
{
	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);
	painter.setBrush(curColors.clipperColor);
	painter.setPen(curColors.clipperColor);

	if (ui->comboBox->currentIndex() == CLIPPER)
	{
		Line closeLine(clipper.points[clipper.points.size() - 1], clipper.points[0]);
		addLineInFigure(clipper, closeLine);
		if (! isConvex(clipper)) {
			QMessageBox::critical(NULL, "Ошибка", "Отсекатель невыпуклый! Повторите ввод отсекателя.");
			resetFigure(clipper);
			goto draw;
		}
		clipper.isClose = true;
	}
	else if (ui->comboBox->currentIndex() == FIGURE)
	{
		Line closeLine(srcFigure.points[srcFigure.points.size() - 1], srcFigure.points[0]);
		addLineInFigure(srcFigure, closeLine);
		srcFigure.isClose = true;
	}

	draw:
	drawFigure(clipper, &painter);

	painter.setBrush(curColors.clipPolyColor);
	painter.setPen(curColors.clipPolyColor);
	drawFigure(srcFigure, &painter);

	QPixmap pixmap = QPixmap::fromImage(image);
	scene->clear();
	scene->addPixmap(pixmap);
}


void MainWindow::on_pushButton_7_clicked()
{
	resetFigure(clipper);
	resetFigure(destFigure);
	resetFigure(srcFigure);

	ui->listWidget->clear();
	ui->listWidget_2->clear();

	ui->lineEdit->clear();
	ui->lineEdit_2->clear();

	ui->listWidget->insertItem(0, QString("Отсекатель"));
	ui->listWidget_2->insertItem(0, QString("Многоугольник"));

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPixmap pixmap = QPixmap::fromImage(image);
	scene->clear();
	scene->addPixmap(pixmap);
}



void MainWindow::on_pushButton_4_clicked()
{
	bool ok1, ok2;

	int x = ui->lineEdit->text().toInt(&ok1);
	int y = ui->lineEdit_2->text().toInt(&ok2);

	if (!ok1 || !ok2)
		return;

	ui->lineEdit->clear();
	ui->lineEdit_2->clear();

	QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);

	Point p(x, y);

	if (ui->comboBox->currentIndex() == CLIPPER) {
		painter.setBrush(curColors.clipperColor);
		painter.setPen(curColors.clipperColor);
		addPointInFigure(clipper, p);
		addPointInList(ui->listWidget, p);
		if (clipper.points.size() > 1)
			addLineInFigure(clipper, Line(clipper.points[clipper.points.size() - 2], p));
	}
	else if (ui->comboBox->currentIndex() == FIGURE) {
		painter.setBrush(curColors.clipPolyColor);
		painter.setPen(curColors.clipPolyColor);
		addPointInFigure(srcFigure, p);
		addPointInList(ui->listWidget_2, p);
		if (srcFigure.points.size() > 1)
			addLineInFigure(srcFigure, Line(srcFigure.points[srcFigure.points.size() - 2], p));
	}

	draw(clipper, srcFigure, destFigure, &painter, curColors);
	QPixmap pixmap = QPixmap::fromImage(image);
	scene->clear();
	scene->addPixmap(pixmap);
}


void MainWindow::on_pushButton_8_clicked()
{
	undoStack->undo();
}

