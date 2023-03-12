#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	scene = new QGraphicsScene();

	undoStack = new QUndoStack(this);

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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
	delete undoStack;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	if (event->angleDelta().y() > 0)
		ui->graphicsView->scale(SCALE, SCALE);
	else
		ui->graphicsView->scale(1 / SCALE, 1 / SCALE);
}

void MainWindow::read_line(line_segment_t &line) // добавить проверки
{
    bool ok1, ok2, ok3, ok4;

    line.start_x = ui->lineEdit->text().toDouble(&ok1);
    line.start_y = ui->lineEdit_2->text().toDouble(&ok2);
    line.finish_x = ui->lineEdit_3->text().toDouble(&ok3);
    line.finish_y = ui->lineEdit_4->text().toDouble(&ok4);

	line.color = current_state.line_color;
}

void MainWindow::read_spectre(spectre_t &spectre) // тут тоже
{
	bool ok1, ok2, ok3, ok4;

	spectre.center_x = ui->lineEdit_5->text().toDouble(&ok1);
	spectre.center_y = ui->lineEdit_6->text().toDouble(&ok2);
	spectre.len = ui->lineEdit_7->text().toDouble(&ok3);
	spectre.angle = ui->lineEdit_8->text().toDouble(&ok4);

	spectre.color = current_state.line_color;
}

void MainWindow::on_pushButton_4_clicked() // построение отрезка
{
    line_segment_t line;

	read_line(line);

	ui->graphicsView->setBackgroundBrush(current_state.sceneColor);

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
		bresenham_without_gradation(line, scene, false);
		break;
	case WU:
		wu_algorithm(line, scene, false);
		break;
    }

	current_state.lines.push_back(line);
	QUndoCommand *addLine = new AddLine(current_state, scene);
	undoStack->push(addLine);
}

void MainWindow::on_pushButton_6_clicked()
{
	scene->clear();
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
	scene_color = current_state.sceneColor;
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

	read_spectre(spectre);
	line.color = current_state.line_color;
	line.start_x = spectre.center_x;
	line.start_y = spectre.center_y;

	double x = line.start_x + spectre.len;
	double y = line.start_y;

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
			bresenham_without_gradation(line, scene, false);
			break;
		case WU:
			wu_algorithm(line, scene, false);
			break;
		}
	}

	current_state.spectres.push_back(spectre);
}

void MainWindow::on_pushButton_5_clicked()
{
	const QUndoCommand *command = undoStack->command(undoStack->count() - 1);
	int id = command->id();

	switch (id) {
		case 0:
			ui->graphicsView->setBackgroundBrush(scene_color);
			break;
	}

	undoStack->undo();
}

