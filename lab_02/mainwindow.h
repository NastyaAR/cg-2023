#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "event_handler.h"
#include <vector>

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
    void on_transfer_clicked();

    void on_scaling_clicked();

    void on_turn_clicked();

    void on_loading_clicked();

    void on_cancel_btn_clicked();

    void about();

    void about_me();

private:
    canvas_t init_canvas();
    void handle_all(const err_t rc);
    err_t read_angles(turn_t &turn);
    err_t read_transfer(transfer_t &transfer);
    err_t read_scale(scale_t &scale);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
