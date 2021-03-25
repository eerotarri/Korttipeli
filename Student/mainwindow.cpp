#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "configurationwindow.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(mScene);

    ConfigurationWindow c;
    c.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
