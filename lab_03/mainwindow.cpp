#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

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
    ui->label->setStyleSheet("background-color: black");
    ui->label_2->setStyleSheet("background-color: white");

	QAction *about_act = ui->menubar->addAction("О программе");
	connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
	QAction *about_me_act = ui->menubar->addAction("Об авторе");
	connect(about_me_act, SIGNAL(triggered()), this, SLOT(about_me()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
	delete undoStack;
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

err_t MainWindow::read_line(line_segment_t &line)
{
    bool ok1, ok2, ok3, ok4;

    line.start_x = ui->lineEdit->text().toDouble(&ok1);
    line.start_y = ui->lineEdit_2->text().toDouble(&ok2);
    line.finish_x = ui->lineEdit_3->text().toDouble(&ok3);
    line.finish_y = ui->lineEdit_4->text().toDouble(&ok4);

	if (!ok1 || !ok2 || !ok3 || !ok4)
		return INCORRECT_LINE;

	if (line.start_x == line.finish_x && line.start_y == line.finish_y)
		return MATCHING_POINTS_ERR;

	line.color = current_state.line_color;

	return SUCCESS;
}

err_t MainWindow::read_spectre(spectre_t &spectre)
{
	bool ok1, ok2, ok3, ok4;

	spectre.center_x = ui->lineEdit_5->text().toDouble(&ok1);
	spectre.center_y = ui->lineEdit_6->text().toDouble(&ok2);
	spectre.len = ui->lineEdit_7->text().toDouble(&ok3);
	spectre.angle = ui->lineEdit_8->text().toDouble(&ok4);

	if (!ok1 || !ok2 || !ok3 || !ok4 || spectre.len == 0 || spectre.angle == 0)
		return INCORRECT_SPECTRE;

	spectre.color = current_state.line_color;

	return SUCCESS;
}

void MainWindow::on_pushButton_4_clicked() // построение отрезка
{
    line_segment_t line;
	err_t rc = SUCCESS;

	if ((rc = read_line(line)) != 0)
	{
		handle_error(rc);
		return;
	}

	scene_colors.push_back(current_state.sceneColor);

	ui->graphicsView->setBackgroundBrush(current_state.sceneColor);

    switch (ui->comboBox->currentIndex()) {
    case STANDART:
		lib_algorithm(line, scene);
		line.method = STANDART;
        break;
    case DDA:
		dda_algorithm(line, scene);
		line.method = DDA;
        break;
	case BRESENHAM_REAL:
		double_bresenham_algorithm(line, scene);
		line.method = BRESENHAM_REAL;
		break;
	case BRESENHAM_INT:
		int_bresenham_algorithm(line, scene);
		line.method = BRESENHAM_INT;
		break;
	case BRESENHAM_NO_GRADATION:
		bresenham_without_gradation(line, scene);
		line.method = BRESENHAM_NO_GRADATION;
		break;
	case WU:
		wu_algorithm(line, scene);
		line.method = WU;
		break;
    }

	current_state.lines.push_back(line);
	QUndoCommand *addLine = new AddLine(current_state, scene);
	undoStack->push(addLine);
}

void MainWindow::on_pushButton_6_clicked()
{
	scene_colors.push_back(current_state.sceneColor);
	QUndoCommand *deleteAll = new DeleteAll(current_state, scene);
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
	update_color_on_label(ui->label, current_state.line_color);
}

void MainWindow::on_pushButton_2_clicked()
{
	current_state.sceneColor = QColorDialog::getColor();
	update_color_on_label(ui->label_2, current_state.sceneColor);
}

static double to_radians(double angle)
{
	return M_PI / 180 * angle;
}

void MainWindow::on_pushButton_3_clicked() // построение спектра
{
	line_segment_t line;
	spectre_t spectre;
	err_t rc = SUCCESS;

	if ((rc = read_spectre(spectre)) != 0)
	{
		handle_error(rc);
		return;
	}

	line.color = current_state.line_color;
	line.start_x = spectre.center_x;
	line.start_y = spectre.center_y;

	double x = line.start_x + spectre.len;
	double y = line.start_y;

	spectre.method = (Method_t) ui->comboBox->currentIndex();

	scene_colors.push_back(current_state.sceneColor);

	ui->graphicsView->setBackgroundBrush(current_state.sceneColor);

	for (double angle = 0; angle < 360; angle += spectre.angle)
	{
		x = spectre.len * cos(to_radians(angle)) + line.start_x;
		y = spectre.len * sin(to_radians(angle)) + line.start_y;

		line.finish_x = x;
		line.finish_y = y;

		switch (ui->comboBox->currentIndex()) {
		case STANDART:
			lib_algorithm(line, scene);
			break;
		case DDA:
			dda_algorithm(line, scene);
			break;
		case BRESENHAM_REAL:
			double_bresenham_algorithm(line, scene);
			break;
		case BRESENHAM_INT:
			int_bresenham_algorithm(line, scene);
			break;
		case BRESENHAM_NO_GRADATION:
			bresenham_without_gradation(line, scene);
			break;
		case WU:
			wu_algorithm(line, scene);
			break;
		}
	}

	current_state.spectres.push_back(spectre);
	QUndoCommand *addSpectre = new AddSpectre(current_state, scene);
	undoStack->push(addSpectre);
}

void MainWindow::on_pushButton_5_clicked()
{
	const QUndoCommand *command = undoStack->command(undoStack->count() - 1);

	ui->graphicsView->setBackgroundBrush(scene_colors[scene_colors.size() - 1]);
	scene_colors.pop_back();

	undoStack->undo();
}


static double get_avg_time(spectre_t &spectre, QGraphicsScene *scene, void (*algorithm) (const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number))
{
	line_segment_t line;
	line.color = spectre.color;
	line.start_x = spectre.center_x;
	line.start_y = spectre.center_y;

	double x = line.start_x + spectre.len;
	double y = line.start_y;

	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed_ms = 0;

	double sum = 0;
	for (int i = 0; i < HOW_TIMES; i++)
	{
		begin = std::chrono::high_resolution_clock::now();
		for (double angle = 0; angle < 360; angle += spectre.angle)
		{
			x = spectre.len * cos(to_radians(angle)) + line.start_x;
			y = spectre.len * sin(to_radians(angle)) + line.start_y;

			line.finish_x = x;
			line.finish_y = y;

			algorithm(line, scene, false, NULL);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_ms = (double) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		sum += elapsed_ms;
	}

	return sum / HOW_TIMES;
}


void MainWindow::on_pushButton_7_clicked()
{
	FILE *file = fopen("time.txt", "w");
	if (! file)
	{
		handle_error(FILE_OPEN_ERROR);
		return;
	}

	spectre_t spectre = {0, 0, 10, 1000, STANDART, QColor(0, 0, 0, 255)};

	fprintf(file, "%lf ", get_avg_time(spectre, scene, lib_algorithm));
	fprintf(file, "%lf ", get_avg_time(spectre, scene, dda_algorithm));
	fprintf(file, "%lf ", get_avg_time(spectre, scene, double_bresenham_algorithm));
	fprintf(file,"%lf ", get_avg_time(spectre, scene, int_bresenham_algorithm));
	fprintf(file, "%lf ", get_avg_time(spectre, scene, bresenham_without_gradation));
	fprintf(file, "%lf", get_avg_time(spectre, scene, wu_algorithm));

	fclose(file);

	std::system("python3 /home/nastya/sem4/cg-2023/lab_03/graph_time.py");
}

static void get_step_number(spectre_t &spectre, QGraphicsScene *scene, void (*algorithm) (const line_segment_t &line, QGraphicsScene *scene, bool draw, int *step_number), FILE *file)
{
	line_segment_t line;
	line.color = spectre.color;
	line.start_x = spectre.center_x;
	line.start_y = spectre.center_y;

	double x = line.start_x + spectre.len;
	double y = line.start_y;

	int step_number = 0;

	for (double angle = 0; angle <= 90; angle += spectre.angle)
	{
		x = spectre.len * cos(to_radians(angle)) + line.start_x;
		y = spectre.len * sin(to_radians(angle)) + line.start_y;

		line.finish_x = x;
		line.finish_y = y;

		algorithm(line, scene, false, &step_number);

		fprintf(file, "%d ", step_number);
		step_number = 0;
	}
}

void MainWindow::on_pushButton_8_clicked()
{
	FILE *file = fopen("gradation.txt", "w");
	if (! file)
	{
		handle_error(FILE_OPEN_ERROR);
		return;
	}

	spectre_t spectre = {0, 0, 1, 1000, STANDART, QColor(0, 0, 0, 255)};

	get_step_number(spectre, scene, dda_algorithm, file);
	fprintf(file, "\n");
	get_step_number(spectre, scene, double_bresenham_algorithm, file);
	fprintf(file, "\n");
	get_step_number(spectre, scene, int_bresenham_algorithm, file);
	fprintf(file, "\n");
	get_step_number(spectre, scene, bresenham_without_gradation, file);
	fprintf(file, "\n");
	get_step_number(spectre, scene, wu_algorithm, file);

	fclose(file);

	std::system("python3 /home/nastya/sem4/cg-2023/lab_03/steps.py");
}

