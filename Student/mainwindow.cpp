#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "configurationwindow.hh"
#include "player.h"
#include "location.h"
#include "settingsreader.h"
#include "runner.h"
#include "agent.hh"

#include <QFile>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLabel>

#include <QDebug>

static int CARD_WIDTH = 70;
static int CARD_HEIGHT = 100;
static int PADDING_Y = 20;
static int PADDING_X = 7;

const std::vector<QString> LOCATIONS = {"Castle", "Marketplace", "Forest", "Slums"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // We need a graphics scene in which to draw rectangles
    scene_1 = new QGraphicsScene(ui->graphicsView);
    scene_2 = new QGraphicsScene(ui->graphicsView_2);
    scene_3 = new QGraphicsScene(ui->graphicsView_3);
    scene_4 = new QGraphicsScene(ui->graphicsView_4);
    scene_hand = new QGraphicsScene(ui->graphicsView_hand);

    ui->graphicsView->setScene(scene_1);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView_3->setScene(scene_3);
    ui->graphicsView_4->setScene(scene_4);
    ui->graphicsView_hand->setScene(scene_hand);

//    QLabel* label1 = new QLabel();
//    label1->setText(LOCATIONS.at(0));
//    QLabel* label2 = new QLabel();
//    label2->setText(LOCATIONS.at(1));

//    QLabel* label3 = new QLabel();
//    label3->setText(LOCATIONS.at(2));
//    QLabel* label4 = new QLabel();
//    label4->setText(LOCATIONS.at(3));
//    QLabel* current_player_hand = new QLabel();
//    current_player_hand->setText("HAND");

//    scene_1->addWidget(label1);
//    scene_2->addWidget(label2);
//    scene_3->addWidget(label3);
//    scene_4->addWidget(label4);
//    scene_hand->addWidget(current_player_hand);



    ConfigurationWindow c;
    c.exec();

//    qDebug() << ui->label;


    // Initializes the static state of the game
    std::shared_ptr<Interface::Game> g = std::make_shared<Interface::Game>();

    // Initializes the static runner
    Interface::Runner r(g);

    g->addPlayer(QString::fromStdString("Niilo"));
    g->addPlayer(QString::fromStdString("Eero"));


    for (unsigned short int i = 0; i < 4; i++) {
        std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(i, LOCATIONS.at(i));
        g->addLocation(new_location);
    }

    addCard();

//    Agent* punainen_pallero = new Agent(punanen);
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

void MainWindow::addCard()
{
    QPushButton* punanen = new QPushButton();
    scene_hand->addWidget(punanen);
    punanen->setParent(ui->graphicsView_hand);
    punanen->setGeometry(-451, 0, CARD_WIDTH, CARD_HEIGHT);

    connect(punanen, &QPushButton::clicked, this, &MainWindow::toimii);
}

void MainWindow::toimii()
{
    qDebug() << "toimmii";
}
