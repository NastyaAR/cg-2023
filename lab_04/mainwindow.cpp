#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->lineEdit_11->setEnabled(false);

	scene = new QGraphicsScene();

	undoStack = new QUndoStack(this);

	scene_colors.push_back(QColor(255, 255, 255, 255));

	ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft); // изначально сцена в верхнем левом углу
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); // перетаскивание сцены по лкм
	ui->graphicsView->setRenderHint(QPainter::Antialiasing); // отключение сглаживания
	ui->graphicsView->setScene(scene);

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

	circle.method = (method_t) ui->comboBox->currentIndex();

	circle.color = current_state.line_color;
}

void MainWindow::read_ellipse(ellipse_t &ellipse) // проверки
{
	bool ok1, ok2, ok3, ok4;

	ellipse.centerX = ui->lineEdit->text().toDouble(&ok1);
	ellipse.centerY = ui->lineEdit_2->text().toDouble(&ok2);
	ellipse.a = ui->lineEdit_4->text().toDouble(&ok3);
	ellipse.b = ui->lineEdit_5->text().toDouble(&ok4);

	ellipse.method = (method_t) ui->comboBox->currentIndex();

	ellipse.color = current_state.line_color;
}

void MainWindow::read_circle_spectre(circle_spectre_t &circle_spectre)
{
	bool ok1, ok2, ok3, ok4, ok5;

	circle_spectre.centerX = ui->lineEdit_6->text().toDouble(&ok1);
	circle_spectre.centerY = ui->lineEdit_7->text().toDouble(&ok2);

	circle_spectre.beginR = ui->lineEdit_8->text().toDouble(&ok3);

	circle_spectre.color = current_state.line_color;

	circle_spectre.method = (method_t) ui->comboBox->currentIndex();

	if (! ui->lineEdit_11->isEnabled())
	{
		circle_spectre.variable.first.endR = ui->lineEdit_9->text().toDouble(&ok4);
		circle_spectre.variable.first.step = ui->lineEdit_10->text().toDouble(&ok5);
		circle_spectre.variant = 1;
	}
	else if (! ui->lineEdit_10->isEnabled())
	{
		circle_spectre.variable.second.endR = ui->lineEdit_9->text().toDouble(&ok4);
		circle_spectre.variable.second.number = ui->lineEdit_11->text().toInt(&ok5);
		circle_spectre.variant = 2;
	}
	else
	{
		circle_spectre.variable.third.number = ui->lineEdit_11->text().toInt(&ok4);
		circle_spectre.variable.third.step = ui->lineEdit_10->text().toDouble(&ok5);
		circle_spectre.variant = 3;
	}
}

void MainWindow::read_ellipse_spectre(ellipse_spectre_t &ellipse_spectre)
{
	bool ok1, ok2, ok3, ok4, ok5, ok6;

	ellipse_spectre.beginA = ui->lineEdit_12->text().toDouble(&ok1);
	ellipse_spectre.beginB = ui->lineEdit_14->text().toDouble(&ok2);
	ellipse_spectre.centerX = ui->lineEdit_6->text().toDouble(&ok3);
	ellipse_spectre.centerY = ui->lineEdit_7->text().toDouble(&ok4);

	ellipse_spectre.color = current_state.line_color;

	ellipse_spectre.method = (method_t) ui->comboBox->currentIndex();

	if (! ui->lineEdit_11->isEnabled())
	{
		ellipse_spectre.variable.first.endA = ui->lineEdit_13->text().toDouble(&ok5);
		ellipse_spectre.variable.first.step = ui->lineEdit_10->text().toDouble(&ok6);
		ellipse_spectre.variant = 1;
	}
	else if (! ui->lineEdit_10->isEnabled())
	{
		ellipse_spectre.variable.second.endA = ui->lineEdit_13->text().toDouble(&ok5);
		ellipse_spectre.variable.second.number = ui->lineEdit_11->text().toInt(&ok6);
		ellipse_spectre.variant = 2;
	}
	else
	{
		ellipse_spectre.variable.third.number = ui->lineEdit_11->text().toInt(&ok5);
		ellipse_spectre.variable.third.step = ui->lineEdit_10->text().toDouble(&ok6);
		ellipse_spectre.variant = 3;
	}
}

void MainWindow::on_pushButton_3_clicked()
{
	circle_t circle;
	ellipse_t ellipse;

	ui->graphicsView->setBackgroundBrush(current_state.sceneColor);

	scene_colors.push_back(current_state.sceneColor);

	if (ui->comboBox_2->currentIndex() == 0)
	{
		read_circle(circle);
		draw_circle(circle);
		current_state.circles.push_back(circle);
		QUndoCommand *addCircle = new AddItem(current_state, scene, ADD_CIRCLE);
		undoStack->push(addCircle);
	}
	else
	{
		read_ellipse(ellipse);
		draw_ellipse(ellipse);
		current_state.circles.push_back(circle);
		QUndoCommand *addEllipse = new AddItem(current_state, scene, ADD_ELLIPSE);
		undoStack->push(addEllipse);
	}
}


void MainWindow::on_pushButton_6_clicked()
{
	scene_colors.push_back(current_state.sceneColor);
	QUndoCommand *deleteAll = new AddItem(current_state, scene, DELETE_ALL);
	undoStack->push(deleteAll);
	scene->clear();
	ui->graphicsView->setBackgroundBrush(QColor(255, 255, 255, 255));
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
	current_state.line_color = QColorDialog::getColor();
	update_color_on_label(ui->label_2, current_state.line_color);
}

void MainWindow::on_pushButton_2_clicked()
{
	current_state.sceneColor = QColorDialog::getColor();
	update_color_on_label(ui->label_3, current_state.sceneColor);
}

void MainWindow::setEnabledAll()
{
	ui->lineEdit_8->setEnabled(true);
	ui->lineEdit_9->setEnabled(true);
	ui->lineEdit_10->setEnabled(true);
	ui->lineEdit_11->setEnabled(true);
	ui->lineEdit_12->setEnabled(true);
	ui->lineEdit_13->setEnabled(true);
	ui->lineEdit_14->setEnabled(true);
}

void MainWindow::on_radioButton_3_clicked()
{
	setEnabledAll();

	ui->lineEdit_11->setEnabled(false);
}


void MainWindow::on_radioButton_clicked()
{
	setEnabledAll();

	ui->lineEdit_10->setEnabled(false);
}


void MainWindow::on_radioButton_4_clicked()
{
	setEnabledAll();

	ui->lineEdit_9->setEnabled(false);
	ui->lineEdit_13->setEnabled(false);
}

void MainWindow::draw_circle(circle_t &circle)
{
	switch (circle.method) {
	case STANDART:
		lib_algorithm(circle, scene);
		break;
	case CANONICAL:
		canonical_algorithm(circle, scene);
		break;
	case PARAMETRIC:
		parametric_algorithm(circle, scene);
		break;
	case BRESENHAM:
		bresenham_circle(circle, scene);
		break;
	case MIDDLE_POINT:
		middle_point(circle, scene);
		break;
	}
}

void MainWindow::draw_ellipse(ellipse_t &ellipse)
{
	switch (ellipse.method) {
	case STANDART:
		lib_algorithm(ellipse, scene);
		break;
	case CANONICAL:
		canonical_algorithm(ellipse, scene);
		break;
	case PARAMETRIC:
		parametric_algorithm(ellipse, scene);
		break;
	case BRESENHAM:
		bresenham_ellipse(ellipse, scene);
		break;
	case MIDDLE_POINT:
		middle_point(ellipse, scene);
		break;
	}
}

void MainWindow::on_pushButton_4_clicked()
{
	circle_t circle;
	ellipse_t ellipse;

	circle_spectre_t circle_spectre;
	ellipse_spectre_t ellipse_spectre;

	double step;
	double R;
	double A, B;

	ui->graphicsView->setBackgroundBrush(current_state.sceneColor);

	scene_colors.push_back(current_state.sceneColor);

	if (ui->comboBox_2->currentIndex() == 0)
	{
		read_circle_spectre(circle_spectre);

		circle.method = circle_spectre.method;
		circle.centerX = circle_spectre.centerX;
		circle.centerY = circle_spectre.centerY;
		circle.color = circle_spectre.color;

		switch (circle_spectre.variant)
		{
		case 1:
			for (R = circle_spectre.beginR; R < circle_spectre.variable.first.endR; R += circle_spectre.variable.first.step)
			{
				circle.r = R;
				draw_circle(circle);
			}
			break;
		case 2:
			step = (circle_spectre.variable.second.endR - circle_spectre.beginR) / circle_spectre.variable.second.number;
			for (R = circle_spectre.beginR; R < circle_spectre.variable.second.endR; R += step)
			{
				circle.r = R;
				draw_circle(circle);
			}
			break;
		case 3:
			R = circle_spectre.beginR;
			for (int i = 0; i < circle_spectre.variable.third.number; i++)
			{
				R += (i * circle_spectre.variable.third.step);
				circle.r = R;

				draw_circle(circle);
			}
			break;
		}

		current_state.circle_spectres.push_back(circle_spectre);
		QUndoCommand *addCircleSpectre = new AddItem(current_state, scene, ADD_CIRCLE_SPECTRE);
		undoStack->push(addCircleSpectre);
	}
	else
	{
		read_ellipse_spectre(ellipse_spectre);

		ellipse.method = ellipse_spectre.method;
		ellipse.centerX = ellipse_spectre.centerX;
		ellipse.centerY = ellipse_spectre.centerY;
		ellipse.color = ellipse_spectre.color;

		switch (ellipse_spectre.variant) {
		case 1:
			for (double A = ellipse_spectre.beginA, B = ellipse_spectre.beginB; A < ellipse_spectre.variable.first.endA; \
				 A += ellipse_spectre.variable.first.step, B += ellipse_spectre.variable.first.step)
			{
				ellipse.a = A;
				ellipse.b = B;
				draw_ellipse(ellipse);
			}
			break;
		case 2:
			step = (ellipse_spectre.variable.second.endA - ellipse_spectre.beginA) / ellipse_spectre.variable.second.number;
			for (double A = ellipse_spectre.beginA, B = ellipse_spectre.beginB; A < ellipse_spectre.variable.second.endA; \
				 A += step, B += step)
			{
				ellipse.a = A;
				ellipse.b = B;
				draw_ellipse(ellipse);
			}
			break;
		case 3:
			A = ellipse_spectre.beginA;
			B = ellipse_spectre.beginB;
			for (int i = 0; i < ellipse_spectre.variable.third.number; i++)
			{
				A += (i * ellipse_spectre.variable.third.step);
				B += (i * ellipse_spectre.variable.third.step);
				ellipse.a = A;
				ellipse.b = B;
				draw_ellipse(ellipse);
			}
			break;
		}
	}
}



void MainWindow::on_pushButton_5_clicked()
{
	ui->graphicsView->setBackgroundBrush(scene_colors[scene_colors.size() - 1]);
	scene_colors.pop_back();

	undoStack->undo();
}

static double get_avg_time(QGraphicsScene *scene, void (*algorithm) (const circle_t &circle, QGraphicsScene *scene, bool draw), bool cflag)
{
	circle_t circle = {.centerX = 0, .centerY = 0, .color = Qt::black};

	double sum = 0;

	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed_ms = 0;

	for (int i = 0; i < REPEAT; i++)
	{
		begin = std::chrono::high_resolution_clock::now();
		for (double R = 10; R < MAX_R; R += 10)
		{
			circle.r = R;
			algorithm(circle, scene, false);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_ms = (double) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		sum += elapsed_ms;
	}

	return sum / REPEAT;
}

static double get_avg_time(QGraphicsScene *scene, void (*algorithm) (const ellipse_t &ellipse, QGraphicsScene *scene, bool draw))
{
	ellipse_t ellipse = {.centerX = 0, .centerY = 0, .color = Qt::black};
	double sum = 0;
	double B = 0;

	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed_ms = 0;

	for (int i = 0; i < REPEAT; i++)
	{
		begin = std::chrono::high_resolution_clock::now();
		for (double A = 10; A < MAX_A; A += 10, B += 5)
		{
			ellipse.a = A;
			ellipse.b = B;
			algorithm(ellipse, scene, false);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_ms = (double) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		sum += elapsed_ms;
	}

	return sum / REPEAT;
}

void MainWindow::on_pushButton_7_clicked()
{
	FILE *file = fopen("circle_time.txt", "w");
	fprintf(file, "%lf ", get_avg_time(scene, lib_algorithm, true));
	fprintf(file, "%lf ", get_avg_time(scene, canonical_algorithm, true));
	fprintf(file, "%lf ", get_avg_time(scene, parametric_algorithm, true));
	fprintf(file, "%lf ", get_avg_time(scene, bresenham_circle, true));
	fprintf(file, "%lf", get_avg_time(scene, middle_point, true));
	fclose(file);

	file = fopen("ellipse_time.txt", "w");
	fprintf(file, "%lf ", get_avg_time(scene, lib_algorithm));
	fprintf(file, "%lf ", get_avg_time(scene, canonical_algorithm));
	fprintf(file, "%lf ", get_avg_time(scene, parametric_algorithm));
	fprintf(file, "%lf ", get_avg_time(scene, bresenham_ellipse));
	fprintf(file, "%lf", get_avg_time(scene, middle_point));
	fclose(file);

	std::system("python3 /home/nastya/sem4/cg-2023/lab_04/graph_time.py");
}

