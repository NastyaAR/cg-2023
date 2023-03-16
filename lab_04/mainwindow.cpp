#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	scene = new QGraphicsScene();

	undoStack = new QUndoStack(this);

	scene_colors.push_back(QColor(255, 255, 255, 255));

	ui->graphicsView->setScene(scene);
	ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft); // изначально сцена в верхнем левом углу
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); // перетаскивание сцены по лкм
	ui->graphicsView->setRenderHint(QPainter::Antialiasing, false); // отключение сглаживания

	ui->graphicsView->viewport()->installEventFilter(this); // всё, что происходит в qgraphicsview отправляется в обработчик EventFilter

	current_state.sceneColor = QColor(255, 255, 255, 255);
	ui->label_2->setStyleSheet("background-color: black");
	ui->label_3->setStyleSheet("background-color: white");

	QAction *about_act = ui->menubar->addAction("О программе");
	connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
	QAction *about_me_act = ui->menubar->addAction("Об авторе");
	connect(about_me_act, SIGNAL(triggered()), this, SLOT(about_me()));
}

MainWindow::~MainWindow()
{
	delete scene;
	delete undoStack;
	delete ui;
}

void MainWindow::about()
{
	QMessageBox::information(this, "О программе", "Программа позволяет рисовать отрезки/спектры отрезков различными алгоритмами.\nРеализована возможность сравнения алгоритмов по времени и ступенчатости.");
}

void MainWindow::about_me()
{
	QMessageBox::information(this, "Об авторе", "Алькина Анастасия ИУ7-44Б МГТУ им. Н.Э.Баумана");
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	if (event->angleDelta().y() > 0)
		ui->graphicsView->scale(SCALE, SCALE);
	else
		ui->graphicsView->scale(1 / SCALE, 1 / SCALE);
}

void MainWindow::read_circle(circle_t &circle) // проверки
{
	bool ok1, ok2, ok3;

	circle.centerX = ui->lineEdit->text().toDouble(&ok1);
	circle.centerY = ui->lineEdit_2->text().toDouble(&ok2);
	circle.r = ui->lineEdit_3->text().toDouble(&ok3);

	circle.color = current_state.cur_color;
}

void MainWindow::on_pushButton_3_clicked()
{
	circle_t circle;

}

