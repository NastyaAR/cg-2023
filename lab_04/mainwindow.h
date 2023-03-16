#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QColorDialog>
#include <QUndoStack>
#include <QMessageBox>
#include <chrono>

#include "algorithms.h"

#define SCALE 1.1

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
	void on_pushButton_3_clicked();
	void about();
	void about_me();
	void read_circle(circle_t &circle);

private:
	QGraphicsScene *scene;
	state_t current_state;

	std::vector <QColor> scene_colors;

	QUndoStack *undoStack = nullptr;
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
