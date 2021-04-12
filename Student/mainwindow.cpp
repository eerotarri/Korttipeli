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

const int ACTION_WIDTH = 239;
const int ACTION_HEIGHT = 50;

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

    addCardToPlayer();

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

void MainWindow::addCardToPlayer()
{
    // Adds 3 cards to each player
    for (auto player : game_->players()) {

        for (int i = 0; i < 3; i++) {
            QPushButton* assigned_button = new QPushButton(QString::fromStdString(std::to_string(i + 1)));

            std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>();
//            punainen_pallero->setPlacement();
            punainen_pallero->setButton(assigned_button);
            player->addCard(punainen_pallero);

        }
    }
}

void MainWindow::showCardsInHand()
{
    int i = 0;

    for (auto card : currentPlayer_->cards()) {
        QPushButton* assigned_button = new QPushButton(QString::fromStdString(std::to_string(i + 1)));
        scene_hand->addWidget(assigned_button); // ufoerror
        assigned_button->setGeometry((CARD_WIDTH + PADDING_X) * i, PADDING_Y, CARD_WIDTH, CARD_HEIGHT);

        connect(assigned_button, &QPushButton::clicked, this, &MainWindow::agentClicked);
        i++;
    }

    //    connect(punanen, &QPushButton::clicked, this, &MainWindow::toimii);
}

void MainWindow::agentClicked()
{
    clearScene(scene_actions);

    QPushButton* liiku = new QPushButton("Move to");
    scene_actions->addWidget(liiku);
    liiku->setGeometry(0, 0, 239, 50);

    connect(liiku, &QPushButton::clicked, this, &MainWindow::moveAction);
}

void MainWindow::moveAction()
{
    clearScene(scene_actions);

    int i = 0;
    for (auto location : LOCATIONS) {
        QPushButton* action = new QPushButton(location);
        scene_actions->addWidget(action);
        action->setGeometry(0, ACTION_HEIGHT * i, ACTION_WIDTH, ACTION_HEIGHT);
        ++i;
    }

}

void MainWindow::initializeLocations()
{
    // Creates instance "hand" as location
    std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(0, "Hand");
    game_->addLocation(new_location);

    // Initializes locations to the game
    for (unsigned short int i = 1; i < 5; i++) {
        std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(i, LOCATIONS.at(i));
        game_->addLocation(new_location);
    }

    for (auto location : game_->locations()) {
        qDebug() << location->name();
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
    scene_actions = new QGraphicsScene(ui->graphicsView_actions);
    scene_hand = new QGraphicsScene(ui->graphicsView_hand);

    ui->graphicsView->setScene(scene_1);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView_3->setScene(scene_3);
    ui->graphicsView_4->setScene(scene_4);
    ui->graphicsView_actions->setScene(scene_actions);
    ui->graphicsView_actions->setAlignment(Qt::AlignTop);

    ui->graphicsView_hand->setScene(scene_hand);
}

void MainWindow::addPlayers()
{
    game_->addPlayer(QString::fromStdString("Niilo"));
    game_->addPlayer(QString::fromStdString("Eero"));
}

void MainWindow::clearScene(QGraphicsScene* scene)
{
  QList<QGraphicsItem*> itemsList = scene->items();
  QList<QGraphicsItem*>::iterator iter = itemsList.begin();
  QList<QGraphicsItem*>::iterator end = itemsList.end();
  while(iter != end)
    {
      QGraphicsItem* item = (*iter);
      item->hide();
      iter++;
    }
}
