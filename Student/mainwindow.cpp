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

    // Initializes the static state of the game
    game_ = std::make_shared<Interface::Game>();

    ConfigurationWindow c(this, game_);
    c.exec();

    connect(ui->nextButton, &QAbstractButton::clicked, this, &MainWindow::nextPlayer);

    // Initialize locations
    initializeLocations();

    // Initializes the static runner
    Interface::Runner r(game_);

//    addPlayers();
    currentPlayer_ = game_->currentPlayer();

    addCardToPlayer();


    for (auto player : game_->players()) {
        qDebug() << player->name();
    }
    qDebug() << game_->players().size();
//    for (auto& p : playerCards_) {
//        qDebug() << p.first;
//    }
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
    for (auto player : game_->players()) {
        for (int i = 0; i < 3; i++) {
            QString name = player->name() + QString::fromStdString("\n" + std::to_string(i + 1));
            QPushButton* assigned_button = new QPushButton(name);

            std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>(assigned_button, 0, 0,
                                                                              player, game_->locations().at(0),
                                                                              0, name);
            punainen_pallero->setScene(scene_hand);
            player->addCard(punainen_pallero);
            playerCards_[player->name()].push_back(assigned_button);
        }
    }
}

void MainWindow::showCardsInHand()
{
    clearScene(scene_hand);

    int i = 0;

    for (auto card : game_->currentPlayer()->cards()) {

        QPushButton* assigned_button = std::dynamic_pointer_cast<Agent>(card)->getButton();

        assigned_button->setGeometry((CARD_WIDTH + PADDING_X) * i, 0, CARD_WIDTH, CARD_HEIGHT);
        scene_hand->addWidget(assigned_button);
        connect(assigned_button, &QPushButton::clicked, this, &MainWindow::agentClicked);
        i++;
    }

    for (auto button : playerCards_.at(currentPlayer_->name())) {
        button->setVisible(true);
    }
}

void MainWindow::agentClicked()
{
    clearScene(scene_actions);

    auto button = qobject_cast<QPushButton *>(sender());

    std::shared_ptr<Interface::CardInterface> vittu;

    for (auto agent : game_->currentPlayer()->cards()) {
        if (agent->name() == button->text()) {
            vittu = agent;
        }
    }


    // JOS LUET TÄTÄ NI DYNAMIC_POINTER_CAST ON AIKA JUMALA KORTTI
    // SILLÄ SAA MUUTETTUA CARDINTERFACE TYYPPISEN KUSIPÄÄN AGENTIKS
    // OLETAN ETTÄ TOIMII VAAN KUN SE OIKEESTI ALUNPERIN OLIKI AGENTTI
    // MUTTA EIHÄN ME MUUTA TARVITAKKAA :D
    // LISÄHUOMIONA ETTÄ DYNAMIC_POINTER_CAST TOIMII SMAST POINTTEREILLA
    // KUN PELKKÄ DYNAMIC_CAST TOIMII NORMI POINTTEREILLA

    activeAgent_ = std::dynamic_pointer_cast<Agent>(vittu);

    QPushButton* liiku = new QPushButton("Move to");
    scene_actions->addWidget(liiku);
    liiku->setGeometry(0, 0, 239, 50);
    QPushButton* huijaa = new QPushButton("Swindle");
    scene_actions->addWidget(huijaa);
    huijaa->setGeometry(0, 50, 239, 50);
    QPushButton* tapa = new QPushButton("Stab competitor");
    scene_actions->addWidget(tapa);
    tapa->setGeometry(0, 100, 239, 50);
    unsigned int weak_location = game_->locations().at(0)->id();
    unsigned int vittu_location = vittu->location().lock()->id();
    if (vittu_location == weak_location){
        huijaa->setEnabled(false);
        tapa->setEnabled(false);
    } else {
        huijaa->setEnabled(true);
        if (activeAgent_->scene()->items().size() >= 2) {
            tapa->setEnabled(true);
        } else {
            tapa->setEnabled(false);
        }

    }

    connect(liiku, &QPushButton::clicked, this, &MainWindow::moveAction);
//    connect(huijaa, &QPushButton::clicked, this, &MainWindow::swindleAction);
//    connect(tapa, &QPushButton::clicked, this, &MainWindow::killAction);
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

//void swindleAction()
//{

//}

//void killAction()
//{

//}

void MainWindow::actionClicked()
{
    auto button = qobject_cast<QPushButton *>(sender());

//    activeAgent_->getButton()->hide();
    QGraphicsProxyWidget* proxy = activeAgent_->getButton()->graphicsProxyWidget();
    qDebug() << proxy->geometry();

    if (button->text() == "Castle") {
        if (scene_1->items().size() < 3) {
            scene_1->addItem(proxy);
            activeAgent_->setScene(scene_1);
        }
    } else if (button->text() == "Marketplace") {
        if (scene_2->items().size() < 3) {
            scene_2->addItem(proxy);
            activeAgent_->setScene(scene_2);
        }
    } else if (button->text() == "Forest") {
        if (scene_3->items().size() < 3) {
            scene_3->addItem(proxy);
            activeAgent_->setScene(scene_3);
        }
    } else if (button->text() == "Slums") {
        if (scene_4->items().size() < 3) {
            scene_4->addItem(proxy);
            activeAgent_->setScene(scene_4);
        }
    }
    updateScenes();
    qDebug() << "Castle items: " << scene_1->items().size();



    activeAgent_->getButton()->show();
}

void MainWindow::nextPlayer()
{
    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        button->setEnabled(false);
    }

    game_->nextPlayer();
    currentPlayer_ = game_->currentPlayer();

    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        button->setEnabled(true);
    }

    qDebug() << currentPlayer_->name();

    showCardsInHand();
    clearScene(scene_actions);
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
    ui->graphicsView->setAlignment(Qt::AlignLeft);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView_2->setAlignment(Qt::AlignLeft);
    ui->graphicsView_3->setScene(scene_3);
    ui->graphicsView_3->setAlignment(Qt::AlignLeft);
    ui->graphicsView_4->setScene(scene_4);
    ui->graphicsView_4->setAlignment(Qt::AlignLeft);
    ui->graphicsView_actions->setScene(scene_actions);
    ui->graphicsView_actions->setAlignment(Qt::AlignTop);

    ui->graphicsView_hand->setScene(scene_hand);
}

void MainWindow::updateScenes()
{

    qDebug() << scene_4->items(Qt::AscendingOrder);


    std::vector<QGraphicsScene*> scenes = {scene_1, scene_2, scene_3, scene_4};
    for (QGraphicsScene* scene : scenes){
        int i = 0;
        for (auto item : scene->items(Qt::AscendingOrder)) {
            auto real_item = dynamic_cast<QGraphicsWidget*>(item);
            real_item->setGeometry((CARD_WIDTH) * i, 0, CARD_WIDTH, CARD_HEIGHT);
            ++i;
        }
    }
}


// EI TOIMI VIELÄ :D

void MainWindow::updateHand()
{
    clearScene(scene_hand);
    int i = 0;
    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        button->setGeometry((CARD_WIDTH) * i, 0, CARD_WIDTH, CARD_HEIGHT);
        button->move((CARD_WIDTH) * i, 0);
        scene_hand->addWidget(button);
        connect(button, &QPushButton::clicked, this, &MainWindow::agentClicked);
        ++i;
    }
}

void MainWindow::clearScene(QGraphicsScene* scene)
{
  QList<QGraphicsItem*> itemsList = scene->items();
  QList<QGraphicsItem*>::iterator iter = itemsList.begin();
  QList<QGraphicsItem*>::iterator end = itemsList.end();
  while(iter != end)
    {
      QGraphicsItem* item = (*iter);
      item->setVisible(false);
      iter++;
    }
}
