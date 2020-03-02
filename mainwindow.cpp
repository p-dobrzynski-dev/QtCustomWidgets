#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_2->setValue(ui->horizontalSlider->value());

    connect (ui->horizontalSlider, SIGNAL(valueChanged (int)), ui->widget, SLOT(setValue(int)));
    connect (ui->horizontalSlider, SIGNAL(valueChanged (int)), ui->widget_2, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

