#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Thermometer widget
    ui->thermometerLineEdit->setText(QString::number(ui->Thermometer->getValue()));
    connect(ui->updateThermometerButton, SIGNAL (clicked()),this, SLOT (updateThermometer()));

    // Battery widget
    ui->BatteryLineEdit->setText(QString::number(ui->Battery->getValue()));
    if (ui->Battery->getChargingState()) {
        ui->isChargingBatteryCheckBox->setCheckState(Qt::Checked);
    } else {
        ui->isChargingBatteryCheckBox->setCheckState(Qt::Unchecked);
    }
    connect(ui->updateBatteryButton, SIGNAL (clicked()),this, SLOT (updateBattery()));

    // Tachometer widget
    ui->tachometerValueLineEdit->setText(QString::number(ui->tachometer->getValue()));
    ui->tachometerMaxValueLineEdit->setText(QString::number(ui->tachometer->getMaxValue()));
    connect(ui->updateTachometerButton, SIGNAL (clicked()),this, SLOT (updateTachometer()));

    // Seven segment clock
    ui->sevenSegmentLineEdit->setText(QString::number(ui->SevenSegmentClockWidget->getValue()));
    connect(ui->updateSevenSegmentButton, SIGNAL (clicked()),this, SLOT (updateSevenSegment()));

    // Level
    ui->levelXValueLineEdit->setText(QString::number(ui->level->getXAngle()));
    ui->levelYValueLineEdit->setText(QString::number(ui->level->getYAngle()));
    connect(ui->updateLevelButton, SIGNAL (clicked()),this, SLOT (updateLevel()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateThermometer(){
    QString value = ui->thermometerLineEdit->text();
    double doubleValue = value.toDouble();
    ui->Thermometer->setValue(doubleValue);
}

void MainWindow::updateBattery(){
    QString value = ui->BatteryLineEdit->text();
    int intValue = value.toInt();
    ui->Battery->setValue(intValue);

    if (ui->isChargingBatteryCheckBox->isChecked()) {
        ui->Battery->setChargingState(true);
    } else {
        ui->Battery->setChargingState(false);
    }
}

void MainWindow::updateTachometer(){
    QString value = ui->tachometerValueLineEdit->text();
    int intValue = value.toInt();
    ui->tachometer->setValue(intValue);

    QString maxValue = ui->tachometerMaxValueLineEdit->text();
    int intMaxValue = maxValue.toInt();
    ui->tachometer->setMaxValue(intMaxValue);
}

void MainWindow::updateSevenSegment() {
    QString value = ui->sevenSegmentLineEdit->text();
    int intValue = value.toInt();
    ui->SevenSegmentClockWidget->setValue(intValue);
}

void MainWindow::updateLevel(){
    QString xValue = ui->levelXValueLineEdit->text();
    float floatXValue = xValue.toFloat();
    ui->level->setXAngle(floatXValue);

    QString yValue = ui->levelYValueLineEdit->text();
    float floatYValue = yValue.toFloat();
    ui->level->setYAngle(floatYValue);
}
