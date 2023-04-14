#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QColorDialog>
#include <QUndoStack>
#include <QMessageBox>
#include <QTimer>
#include <chrono>
#include <QRadioButton>

#include "additem.h"
#include "error_handler.h"

#define SCALE 1.1
#define MAX_R 1000
#define REPEAT 10
#define MAX_A 1000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	void wheelEvent(QWheelEvent *event);
	~MainWindow();

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void about();
	void about_me();
	err_t read_circle(circle_t &circle);
	err_t read_ellipse(ellipse_t &ellipse);
	err_t read_circle_spectre(circle_spectre_t &circle_spectre);
	err_t read_ellipse_spectre(ellipse_spectre_t &ellipse);
	void draw_circle(circle_t &circle);
	void draw_ellipse(ellipse_t &ellipse);
	void setEnabledAll();

	void on_pushButton_6_clicked();

	void on_radioButton_3_clicked();

	void on_radioButton_clicked();

	void on_radioButton_4_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

	void on_pushButton_7_clicked();

private:
	QGraphicsScene *scene;
	state_t current_state;

	std::vector <QColor> scene_colors;

	QUndoStack *undoStack = nullptr;
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
