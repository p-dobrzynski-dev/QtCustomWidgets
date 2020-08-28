#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_2->setValue(ui->horizontalSlider->value());

    connect (ui->horizontalSlider, SIGNAL(valueChanged (int)), ui->widget, SLOT(setValue(int)));
    connect (ui->horizontalSlider, SIGNAL(valueChanged (int)), ui->widget_2, SLOT(setValue(int)));
    connect (ui->horizontalSlider, SIGNAL(valueChanged (int)), ui->widget_3, SLOT(setValue(int)));
    connect (ui->doubleSpinBox , SIGNAL(valueChanged(double)), ui->widget_4, SLOT(setXAngle(double)));
    connect (ui->doubleSpinBox_2 , SIGNAL(valueChanged(double)), ui->widget_4, SLOT(setYAngle(double)));
    connect (ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), ui->widget_5, SLOT(setValue(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

