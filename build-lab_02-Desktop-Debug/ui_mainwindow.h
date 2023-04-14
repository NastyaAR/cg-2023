/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_4;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout_5;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QFormLayout *formLayout_6;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QFormLayout *formLayout_7;
    QPushButton *transfer;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineEdit_17;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_8;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_19;
    QFormLayout *formLayout_9;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_21;
    QFormLayout *formLayout_10;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_22;
    QLineEdit *lineEdit_23;
    QPushButton *scaling;
    QLineEdit *lineEdit_10;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QFormLayout *formLayout_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QFormLayout *formLayout_3;
    QPushButton *turn;
    QPushButton *loading;
    QPushButton *cancel_btn;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1268, 838);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("font: 75 italic 14pt \"Noto Sans\";"));
        lineEdit_2->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        lineEdit_11 = new QLineEdit(centralwidget);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, lineEdit_11);

        lineEdit_12 = new QLineEdit(centralwidget);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setReadOnly(true);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, lineEdit_12);


        verticalLayout_4->addLayout(formLayout_5);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        lineEdit_13 = new QLineEdit(centralwidget);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, lineEdit_13);

        lineEdit_14 = new QLineEdit(centralwidget);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setReadOnly(true);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, lineEdit_14);


        verticalLayout_4->addLayout(formLayout_6);

        formLayout_7 = new QFormLayout();
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        transfer = new QPushButton(centralwidget);
        transfer->setObjectName(QString::fromUtf8("transfer"));
        transfer->setStyleSheet(QString::fromUtf8("font: 81 20pt \"Noto Sans\";"));

        formLayout_7->setWidget(0, QFormLayout::SpanningRole, transfer);


        verticalLayout_4->addLayout(formLayout_7);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lineEdit_17 = new QLineEdit(centralwidget);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setStyleSheet(QString::fromUtf8("font: 75 italic 14pt \"Noto Sans\";"));
        lineEdit_17->setReadOnly(true);

        verticalLayout_5->addWidget(lineEdit_17);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        formLayout_8 = new QFormLayout();
        formLayout_8->setObjectName(QString::fromUtf8("formLayout_8"));
        lineEdit_18 = new QLineEdit(centralwidget);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));

        formLayout_8->setWidget(0, QFormLayout::LabelRole, lineEdit_18);

        lineEdit_19 = new QLineEdit(centralwidget);
        lineEdit_19->setObjectName(QString::fromUtf8("lineEdit_19"));
        lineEdit_19->setReadOnly(true);

        formLayout_8->setWidget(0, QFormLayout::FieldRole, lineEdit_19);


        verticalLayout_6->addLayout(formLayout_8);

        formLayout_9 = new QFormLayout();
        formLayout_9->setObjectName(QString::fromUtf8("formLayout_9"));
        lineEdit_20 = new QLineEdit(centralwidget);
        lineEdit_20->setObjectName(QString::fromUtf8("lineEdit_20"));

        formLayout_9->setWidget(0, QFormLayout::LabelRole, lineEdit_20);

        lineEdit_21 = new QLineEdit(centralwidget);
        lineEdit_21->setObjectName(QString::fromUtf8("lineEdit_21"));
        lineEdit_21->setReadOnly(true);

        formLayout_9->setWidget(0, QFormLayout::FieldRole, lineEdit_21);


        verticalLayout_6->addLayout(formLayout_9);

        formLayout_10 = new QFormLayout();
        formLayout_10->setObjectName(QString::fromUtf8("formLayout_10"));
        lineEdit_9 = new QLineEdit(centralwidget);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        formLayout_10->setWidget(0, QFormLayout::LabelRole, lineEdit_9);

        lineEdit_22 = new QLineEdit(centralwidget);
        lineEdit_22->setObjectName(QString::fromUtf8("lineEdit_22"));

        formLayout_10->setWidget(1, QFormLayout::LabelRole, lineEdit_22);

        lineEdit_23 = new QLineEdit(centralwidget);
        lineEdit_23->setObjectName(QString::fromUtf8("lineEdit_23"));
        lineEdit_23->setReadOnly(true);

        formLayout_10->setWidget(1, QFormLayout::FieldRole, lineEdit_23);

        scaling = new QPushButton(centralwidget);
        scaling->setObjectName(QString::fromUtf8("scaling"));
        scaling->setStyleSheet(QString::fromUtf8("font: 81 20pt \"Noto Sans\";"));

        formLayout_10->setWidget(2, QFormLayout::SpanningRole, scaling);

        lineEdit_10 = new QLineEdit(centralwidget);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));

        formLayout_10->setWidget(0, QFormLayout::FieldRole, lineEdit_10);


        verticalLayout_6->addLayout(formLayout_10);


        verticalLayout_5->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 75 italic 14pt \"Noto Sans\";"));
        lineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(lineEdit);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit_7 = new QLineEdit(centralwidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lineEdit_7);

        lineEdit_8 = new QLineEdit(centralwidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_8);

        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lineEdit_4);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_3);


        verticalLayout->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lineEdit_5);

        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_6);


        verticalLayout->addLayout(formLayout_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        turn = new QPushButton(centralwidget);
        turn->setObjectName(QString::fromUtf8("turn"));
        turn->setStyleSheet(QString::fromUtf8("font: 81 20pt \"Noto Sans\";"));

        formLayout_3->setWidget(1, QFormLayout::SpanningRole, turn);

        loading = new QPushButton(centralwidget);
        loading->setObjectName(QString::fromUtf8("loading"));
        loading->setStyleSheet(QString::fromUtf8("font: 81 20pt \"Noto Sans\";"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, loading);

        cancel_btn = new QPushButton(centralwidget);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        cancel_btn->setStyleSheet(QString::fromUtf8("font: 81 20pt \"Noto Sans\";"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, cancel_btn);


        verticalLayout->addLayout(formLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_7->addLayout(verticalLayout_2);


        formLayout_4->setLayout(0, QFormLayout::LabelRole, verticalLayout_7);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, graphicsView);


        gridLayout->addLayout(formLayout_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1268, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261 \320\260\320\262\321\202\320\276\321\200\320\265", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\276\321\201 \320\275\320\260", nullptr));
        lineEdit_12->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 X", nullptr));
        lineEdit_14->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 Y", nullptr));
        transfer->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270", nullptr));
        lineEdit_17->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\262", nullptr));
        lineEdit_19->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 X", nullptr));
        lineEdit_21->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 Y", nullptr));
        lineEdit_23->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200 Y", nullptr));
        scaling->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200 X", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202 \320\275\320\260", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200 X", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200 Y", nullptr));
        turn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        loading->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        cancel_btn->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
