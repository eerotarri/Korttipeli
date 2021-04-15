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

            std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>(assigned_button, 0, 0, player, game_->locations().at(0), 0, name);

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

        QString currentPlayerName = game_->currentPlayer()->name();

//        Teen l�p�l playerCardsista obsoletee :D
//        QPushButton* assigned_button = playerCards_.at(currentPlayerName).at(i);
//        std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(card);
        QPushButton* assigned_button = std::dynamic_pointer_cast<Agent>(card)->getButton();

        scene_hand->addWidget(assigned_button);
        assigned_button->setGeometry((CARD_WIDTH + PADDING_X) * i, 0, CARD_WIDTH, CARD_HEIGHT);

        connect(assigned_button, &QPushButton::clicked, this, &MainWindow::agentClicked);
        i++;

    }

    for (auto button : playerCards_.at(currentPlayer_->name())) {
        button->show();
    }
}

void MainWindow::agentClicked()
{
    clearScene(scene_actions);

    auto button = qobject_cast<QPushButton *>(sender());

    std::shared_ptr<Interface::CardInterface> vittu;

    for (auto agent : currentPlayer_->cards()) {
        if (agent->name() == button->text()) {
            vittu = agent;
        }
    }

    // JOS LUET T�T� NI DYNAMIC_POINTER_CAST ON AIKA JUMALA KORTTI
    // SILL� SAA MUUTETTUA CARDINTERFACE TYYPPISEN KUSIP��N AGENTIKS
    // OLETAN ETT� TOIMII VAAN KUN SE OIKEESTI ALUNPERIN OLIKI AGENTTI
    // MUTTA EIH�N ME MUUTA TARVITAKKAA :D
    // LIS�HUOMIONA ETT� DYNAMIC_POINTER_CAST TOIMII SMAST POINTTEREILLA
    // KUN PELKK� DYNAMIC_CAST TOIMII NORMI POINTTEREILLA
    activeAgent_ = std::dynamic_pointer_cast<Agent>(vittu);

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

//    activeAgent_->getButton()->hide();
    QGraphicsProxyWidget* proxy = activeAgent_->getButton()->graphicsProxyWidget();
    qDebug() << proxy->geometry();

    if (button->text() == "Castle") {
        if (scene_1->items().size() < 3) {
            scene_1->addItem(proxy);
        }
    } else if (button->text() == "Marketplace") {
        if (scene_2->items().size() < 3) {
            scene_2->addItem(proxy);
        }
    } else if (button->text() == "Forest") {
        if (scene_3->items().size() < 3) {
            scene_3->addItem(proxy);
        }
    } else if (button->text() == "Slums") {
        if (scene_4->items().size() < 3) {
            scene_4->addItem(proxy);
        }
    }
    updateScenes();
    qDebug() << "Castle items: " << scene_1->items().size();



    activeAgent_->getButton()->show();
}

void MainWindow::nextPlayer()
{
    game_->nextPlayer();
    currentPlayer_ = game_->currentPlayer();

    qDebug() << currentPlayer_->name();

    showCardsInHand();
//    updateHand();
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
    qDebug() << "wtf";

    std::vector<QGraphicsScene*> scenes = {scene_1, scene_2, scene_3, scene_4};
    for (QGraphicsScene* scene : scenes){
        int i = 0;
        for (auto item : scene->items()) {
            auto real_item = dynamic_cast<QGraphicsWidget*>(item);
            real_item->setGeometry((CARD_WIDTH + PADDING_X) * i, 0, CARD_WIDTH, CARD_HEIGHT);
            ++i;
        }
    }
}

// EI TOIMI VIEL� :D
void MainWindow::updateHand()
{
    clearScene(scene_hand);

    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        scene_hand->addWidget(button);
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
      item->hide();
      iter++;
    }
}
