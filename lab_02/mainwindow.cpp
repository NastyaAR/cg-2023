#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 771, 771);
    ui->graphicsView->setScene(scene);

    QAction *about_act = ui->menubar->addAction("О программе");
    connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
    QAction *about_me_act = ui->menubar->addAction("Об авторе");
    connect(about_me_act, SIGNAL(triggered()), this, SLOT(about_me()));
}

MainWindow::~MainWindow()
{
    event_t quit_event;

    quit_event.number = QUIT;
    event_handler(quit_event);

    delete ui;
}

void MainWindow::about()
{
    QMessageBox::information(this, "О программе", "Программа позволяет загрузить рисунок, отмасштабировать его, повернуть или перенести.");
}

void MainWindow::about_me()
{
    QMessageBox::information(this, "Об авторе", "Алькина Анастасия ИУ7-44Б МГТУ им. Н.Э.Баумана");
}

void MainWindow::on_transfer_clicked()
{
    transfer_t transfer = {0, 0};

    err_t rc = read_transfer(transfer);
    if (! rc)
    {
        event_t transfer_event = {.number = TRANSFER, .transfer = transfer};
        rc = event_handler(transfer_event);
    }

    handle_all(rc);
}

void MainWindow::on_scaling_clicked()
{
    scale_t scale = {1, 1, {0, 0}};

    err_t rc = read_scale(scale);
    if (! rc)
    {
        event_t scale_event = {.number = SCALE, .scale = scale};
        rc = event_handler(scale_event);
    }

    handle_all(rc);
}


void MainWindow::on_turn_clicked()
{
    turn_t turn = {0, {0, 0}};

    err_t rc = read_angles(turn);
    if (! rc)
    {
        event_t turn_event = {.number = TURN, .turn = turn};
        rc = event_handler(turn_event);
    }

    handle_all(rc);
}


void MainWindow::on_loading_clicked()
{
    event_t event = {.number = LOAD, .filename = "test.txt"};

    err_t rc = event_handler(event);

    handle_all(rc);
}

void MainWindow::handle_all(const err_t rc)
{
    if (! rc)
    {
        canvas_t canvas = init_canvas();
        event_t draw_request = {.number = DRAW, .canvas = canvas};
        event_handler(draw_request);
    }
    else
        error_handler(rc);
}

err_t MainWindow::read_angles(turn_t &turn)
{
    bool ok1 = true;
    bool ok2 = true;
    bool ok3 = true;

    turn.d0 = ui->lineEdit_7->text().toDouble(&ok1);
    turn.center.x = ui->lineEdit_4->text().toDouble(&ok2);
    turn.center.y = ui->lineEdit_5->text().toDouble(&ok3);

    if (! ok1 || ! ok2 || ! ok3)
        return ANGLE_INPUT_ERROR;

    return SUCCESS;
}

err_t MainWindow::read_transfer(transfer_t &transfer)
{
    bool ok1 = true;
    bool ok2 = true;

    transfer.dx = ui->lineEdit_11->text().toDouble(&ok1);
    transfer.dy = ui->lineEdit_13->text().toDouble(&ok2);

    if (! ok1 || ! ok2)
        return TRANSFER_INPUT_ERROR;

    return SUCCESS;
}

err_t MainWindow::read_scale(scale_t &scale)
{
    bool ok1 = true;
    bool ok2 = true;
    bool ok3 = true;
    bool ok4 = true;

    scale.kx = ui->lineEdit_18->text().toDouble(&ok1);
    scale.ky = ui->lineEdit_20->text().toDouble(&ok2);
    scale.center.x = ui->lineEdit_9->text().toDouble(&ok3);
    scale.center.y = ui->lineEdit_22->text().toDouble(&ok4);

    if (! ok1 || ! ok2 || ! ok3 || ! ok4)
        return SCALE_INPUT_ERROR;

    return SUCCESS;
}

canvas_t MainWindow::init_canvas()
{
    static canvas_t canvas;

    canvas.scene = ui->graphicsView->scene();
    canvas.width = canvas.scene->width();
    canvas.height = canvas.scene->height();

    return canvas;
}

void MainWindow::on_cancel_btn_clicked()
{
    event_t event = {.number = CANCEL, .filename = "tmp.txt"};
    err_t rc = event_handler(event);

    handle_all(rc);
}

