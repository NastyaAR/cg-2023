#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QInputDialog>

#include "fill.h"
#include "table.h"

#define SCALE 1.1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent* event);

private slots:
	void on_comboBox_currentIndexChanged(int index);

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

	void on_pushButton_10_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_11_clicked();

	void on_pushButton_5_clicked();

	void on_pushButton_6_clicked();

	void on_pushButton_7_clicked();

	void on_pushButton_8_clicked();

private:
	QGraphicsScene *scene;
	currentColors_t curColors;
	Ui::MainWindow *ui;
	points_t points;
	figures_t figures;
	lines_t lines;

	figure_t curMainFigure;

	bool flag = true;
	bool addHole = false;
	double delay = 0.0;
};
#endif // MAINWINDOW_H
