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
    setupUserInterface();

    ConfigurationWindow c;
    c.exec();

    // Initializes the static state of the game
    game_ = std::make_shared<Interface::Game>();

    // Initializes the static runner
    Interface::Runner r(game_);

    addPlayers();
    currentPlayer_ = game_->currentPlayer();

    addCardToPlayer(game_->players().at(0));

    showCardsInHand();
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

void MainWindow::addCardToPlayer(std::shared_ptr<Interface::Player>)
{
    // Adds 3 cards to each player
    for (auto player : game_->players()) {
        std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>();
        for (int i = 0; i < 3; i++) {
            player->addCard(punainen_pallero);
        }
    }
}

void MainWindow::showCardsInHand()
{
    int i = 0;
    for (auto card : currentPlayer_->cards()) {
        QPushButton* assigned_button = new QPushButton();
        scene_hand->addWidget(assigned_button);
        assigned_button->setParent(ui->graphicsView_hand);
        assigned_button->setGeometry(-450 + (CARD_WIDTH + PADDING_X) * i, 0, CARD_WIDTH, CARD_HEIGHT);
        assigned_button->show();
        i++;
    }

//    connect(punanen, &QPushButton::clicked, this, &MainWindow::toimii);
}

void MainWindow::toimii()
{
    qDebug() << "toimmii";
}

void MainWindow::initializeLocations()
{
    // Initializes locations to the game
    for (unsigned short int i = 0; i < 4; i++) {
        std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(i, LOCATIONS.at(i));
        game_->addLocation(new_location);
    }
}

void MainWindow::setupUserInterface()
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
}

void MainWindow::addPlayers()
{
    game_->addPlayer(QString::fromStdString("Niilo"));
    game_->addPlayer(QString::fromStdString("Eero"));
}
