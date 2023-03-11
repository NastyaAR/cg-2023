#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QColorDialog>
#include <QUndoCommand>
#include <QUndoStack>

#include "line_segment.h"
#include "error_handler.h"

#define SCALE 1.1

enum Method_t
{
    STANDART,
    DDA,
    BRESENHAM_INT,
    BRESENHAM_REAL,
	BRESENHAM_NO_GRADATION,
	WU,
};

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
    void on_pushButton_4_clicked();
    void read_line(line_segment_t &line);
	void read_spectre(spectre_t &spectre);

	void on_pushButton_6_clicked();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

private:
    QGraphicsScene *scene;
    state_t current_state;

	QUndoStack *undoStack = nullptr;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
