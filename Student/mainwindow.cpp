#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "configurationwindow.hh"
#include "player.h"
#include "location.h"
#include "settingsreader.h"
#include <QFile>
#include <QGraphicsView>

#include <QDebug>

static int CARD_WIDTH = 70;
static int CARD_HEIGHT = 100;
static int PADDING_Y = 20;
static int PADDING_X = 7;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // We need a graphics scene in which to draw rectangles
    scene_ = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->show();

    //ui->graphicsView->setGeometry(20, 20, 400, 400);

    ConfigurationWindow c;
    c.exec();

//    qDebug() << ui->label;


    // Initializes the static state of the game
    std::shared_ptr<Interface::Game> g = std::make_shared<Interface::Game>();

    g->addPlayer(QString::fromStdString("Niilo"));
    g->addPlayer(QString::fromStdString("Eero"));

    std::vector<QString> Locations = {"Castle", "Marketplace", "Forest", "Slums"};
    for (unsigned short int i = 0; i < 4; i++) {
        std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(i, Locations.at(i));
        g->addLocation(new_location);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCardDimensions(int width, int height, int padding_x, int padding_y)
{
    CARD_WIDTH = width;
    CARD_HEIGHT = height;
    PADDING_X = padding_x;
    PADDING_Y = padding_y;
}
