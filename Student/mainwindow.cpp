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
#include <QGraphicsProxyWidget>
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

    // Initialize locations
    initializeLocations();

    // Initializes the static runner
    Interface::Runner r(game_);

    addPlayers();
    currentPlayer_ = game_->currentPlayer();

    addCardToPlayer();
    qDebug() << "ass";
    for (auto& p : playerCards_) {
        qDebug() << p.first;
    }
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
    QString playerName = "Niilo";
    for (auto player : game_->players()) {

        for (int i = 0; i < 3; i++) {
            QString name = player->name() + QString::fromStdString("\n" + std::to_string(i + 1));
            QPushButton* assigned_button = new QPushButton(name);

            std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>(assigned_button, 0, 0, player, game_->locations().at(0), 0, name);

            player->addCard(punainen_pallero);
            playerCards_[playerName].push_back(assigned_button);
        }
        QString playerName = "Eero";
    }
}

void MainWindow::showCardsInHand()
{
    int i = 0;

    for (auto card : currentPlayer_->cards()) {

        QString currentPlayerName = game_->currentPlayer()->name();
        qDebug() << currentPlayerName << "test";
        QPushButton* assigned_button = playerCards_.at(currentPlayerName).at(i);
        scene_hand->addWidget(assigned_button);
        assigned_button->setGeometry((CARD_WIDTH + PADDING_X) * i, PADDING_Y, CARD_WIDTH, CARD_HEIGHT);

        connect(assigned_button, &QPushButton::clicked, this, &MainWindow::agentClicked);
        i++;

    }

    //    connect(punanen, &QPushButton::clicked, this, &MainWindow::toimii);
}

void MainWindow::agentClicked()
{
    clearScene(scene_actions);

    auto button = qobject_cast<QPushButton *>(sender());

    auto vittu = game_->currentPlayer()->cards().at(0);

    for (auto agent : currentPlayer_->cards()) {
        if (agent->name() == button->text()) {
            vittu = agent;
        }
    }


    if (Agent* agent = dynamic_cast<Agent*>(vittu.get()))  {
         activeAgent_ = agent;
    }

    qDebug() << button->text();

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
        connect(action, &QPushButton::clicked, this, &MainWindow::actionClicked);

        ++i;
    }

}

void MainWindow::actionClicked()
{
    auto button = qobject_cast<QPushButton *>(sender());

    activeAgent_->getButton()->hide();
    QGraphicsProxyWidget* proxy = activeAgent_->getButton()->graphicsProxyWidget();

    if (button->text() == "Castle") {
        scene_1->addItem(proxy);
    } else if (button->text() == "Marketplace") {
        scene_2->addItem(proxy);
    } else if (button->text() == "Forest") {
        scene_3->addItem(proxy);
    } else if (button->text() == "Slums") {
        scene_4->addItem(proxy);
    }



    activeAgent_->getButton()->show();




}

void setNewLocation() {
    // idea: omat skenet kullekin pelaajalle joista kerrallaan vaan yks ei lukittu?
}

void MainWindow::initializeLocations()
{
    // Creates instance "hand" as location
    std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(0, "Hand");
    game_->addLocation(new_location);

    // Initializes locations to the game
    for (unsigned short int i = 0; i < 4; i++) {
        std::shared_ptr<Interface::Location> new_location = std::make_shared<Interface::Location>(i + 1, LOCATIONS.at(i));
        game_->addLocation(new_location);
    }

    for (auto location : game_->locations()) {
        qDebug() << location->name() << location->id();
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
