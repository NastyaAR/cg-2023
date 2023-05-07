#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWheelEvent>
#include <QUndoStack>
#include "drawcommand.h"


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

private slots:
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent* event);
	void on_pushButton_clicked();
	void about();
	void about_me();

	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

	void on_pushButton_9_clicked();

	void on_pushButton_6_clicked();

	void on_pushButton_5_clicked();

	void on_pushButton_7_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_8_clicked();

private:
	Ui::MainWindow *ui;
	QGraphicsScene *scene;
	currentColors_t curColors;

	figure_t clipper;
	figure_t srcFigure;
	figure_t destFigure;

	QUndoStack *undoStack = nullptr;
};
#endif // MAINWINDOW_H
