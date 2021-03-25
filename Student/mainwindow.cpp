#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "configurationwindow.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConfigurationWindow c;
    c.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
