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

	ui->label_2->setStyleSheet("background-color: lightgreen");
	ui->label_3->setStyleSheet("background-color: pink");
	ui->label_4->setStyleSheet("background-color: lightblue");

	curColors.clipperColor = QColor("#90EE90");
	curColors.clipPolyColor = QColor("#FFC0CB");
	curColors.resultColor = QColor("#ADD8E6");

	QAction *about_act = ui->menubar->addAction("О программе");
	connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
	QAction *about_me_act = ui->menubar->addAction("Об авторе");
	connect(about_me_act, SIGNAL(triggered()), this, SLOT(about_me()));

	initFigure(clipper, curColors.clipperColor, false);
	initFigure(srcFigure, curColors.clipPolyColor, false);
	initFigure(destFigure, curColors.resultColor, false);
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

void MainWindow::on_pushButton_9_clicked()
{
	printf("1\n");
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (ui->comboBox->currentIndex() == INPUT_MODE)
	{
		QRect view = ui->graphicsView->geometry();
		QImage image = QImage(ui->graphicsView->width(), ui->graphicsView->height(), QImage::Format_ARGB32);
		image.fill(Qt::transparent);
		QPainter painter(&image);
		painter.setBrush(curColors.clipperColor);
		painter.setPen(curColors.clipperColor);

		if (view.contains(event->pos())) {
			Point p(event->pos().x() - view.x(), event->pos().y() - view.y() - menuBar()->geometry().height());
			drawPoint(p, &painter);
		}

		QPixmap pixmap = QPixmap::fromImage(image);
		//scene->clear();
		scene->addPixmap(pixmap);
	}
}

