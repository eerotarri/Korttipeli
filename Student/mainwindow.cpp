#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "configurationwindow.hh"
#include "player.h"
#include "location.h"
#include "settingsreader.h"
#include "runner.h"
#include "agent.hh"
#include "manualcontrol.h"

#include <QFile>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QLabel>

#include <QDebug>

static int CARD_WIDTH = 80;
static int CARD_HEIGHT = 100;
//static int PADDING_Y = 20;
static int PADDING_X = 7;

const int ACTION_WIDTH = 239;
const int ACTION_HEIGHT = 50;

const QString READY_TEXT = "Press Ready to pass turn to next player.";

const std::vector<QString> LOCATIONS = {"Castle", "Marketplace", "Forest", "Slums"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setupUserInterface();

    // Initializes the static state of the game
    game_ = std::make_shared<Interface::Game>();
    game_->setActive(true);

    ConfigurationWindow c(this, game_);
    c.exec();

    // Initialize locations
    initializeLocations();

    // Initialize the static runner and set control objects to players
    std::shared_ptr<Interface::Runner> runner = std::make_shared<Interface::Runner>(game_);
    for (auto player : game_->players()) {
        std::shared_ptr<Interface::ManualControl> control_object =
                std::make_shared<Interface::ManualControl>();
        runner->setPlayerControl(player, control_object);
    }


    currentPlayer_ = game_->currentPlayer(); // THIS SHOULD BECOME OBSOLETE

    addCardToPlayer();
    showCardsInHand();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCardToPlayer()
{
    int j = 0;
    for (auto player : game_->players()) {
        for (int i = 0; i < 3; i++) {
            QString name = player->name() + QString::fromStdString("\nAgent: " + std::to_string(i + 1));
            QPushButton* assigned_button = new QPushButton(name);

            std::shared_ptr<Agent> punainen_pallero = std::make_shared<Agent>(assigned_button, 0, 0,
                                                                              player, game_->locations().at(0),
                                                                              0, name);
            punainen_pallero->setScene(scene_hand);
            player->addCard(punainen_pallero);
            QPalette p = palette();
            p.setColor(QPalette::Button, colors_.at(j));
            assigned_button->setPalette(p);
            j++;
            playerCards_[player->name()].push_back(assigned_button);
        }
    }
}

void MainWindow::showCardsInHand()
{
    clearScene(scene_hand);

    size_t turn = turn_;
    if (turn < game_->players().size()){
        int i = 0;
        for (auto card : game_->currentPlayer()->cards()) {

            QPushButton* assigned_button = std::dynamic_pointer_cast<Agent>(card)->getButton();

            assigned_button->setGeometry((CARD_WIDTH + PADDING_X) * i, 0, CARD_WIDTH, CARD_HEIGHT);
            scene_hand->addWidget(assigned_button);
            connect(assigned_button, &QPushButton::clicked, this, &MainWindow::agentClicked);
            i++;
        }
    }



    for (auto card : game_->currentPlayer()->cards()) {
        auto agent = std::dynamic_pointer_cast<Agent>(card);
        auto button = agent->getButton();
        button->setVisible(true);

    }


}

void MainWindow::agentClicked()
{
    ui->textBrowser_2->clear();
    ui->textBrowser_2->setText("The points of the current player among with some other status stuff: "
                               "(a method should print this stuff out whenever the context browser isn't busy");
    clearScene(scene_actions);

    auto button = qobject_cast<QPushButton *>(sender());

    std::shared_ptr<Interface::CardInterface> vittu;

    for (auto agent : game_->currentPlayer()->cards()) {
        if (agent->name() == button->text()) {
            vittu = agent;
        }
    }

    activeAgent_ = std::dynamic_pointer_cast<Agent>(vittu);

    QPushButton* liiku = new QPushButton("Move to");
    scene_actions->addWidget(liiku);
    liiku->setGeometry(0, 0, ACTION_WIDTH, ACTION_HEIGHT);
    QPushButton* huijaa = new QPushButton("Swindle");
    scene_actions->addWidget(huijaa);
    huijaa->setGeometry(0, 50, ACTION_WIDTH, ACTION_HEIGHT);
    QPushButton* tapa = new QPushButton("Stab competitor");
    scene_actions->addWidget(tapa);
    tapa->setGeometry(0, 100, ACTION_WIDTH, ACTION_HEIGHT);
//    unsigned int weak_location = game_->locations().at(0)->id();
//    unsigned int vittu_location = vittu->location().lock()->id();
    if (activeAgent_->scene() == scene_hand){
        huijaa->setEnabled(false);
        tapa->setEnabled(false);
    } else {
        //qDebug() << "mene vittu elseen";
        huijaa->setEnabled(true);
        if (activeAgent_->scene()->items().size() >= 2 and activeAgent_->scene()) {
            tapa->setEnabled(true);
        } else {
            tapa->setEnabled(false);
        }

    }

    connect(liiku, &QPushButton::clicked, this, &MainWindow::moveAction);
    connect(huijaa, &QPushButton::clicked, this, &MainWindow::swindleAction);
    connect(tapa, &QPushButton::clicked, this, &MainWindow::killAction);
}

void MainWindow::moveAction()
{
    clearScene(scene_actions);
    ui->textBrowser_2->clear();
    ui->textBrowser_2->setText("Move command context here TBA");


    int i = 0;
    for (auto location : LOCATIONS) {
        QPushButton* action = new QPushButton(location);
        scene_actions->addWidget(action);
        action->setGeometry(0, ACTION_HEIGHT * i, ACTION_WIDTH, ACTION_HEIGHT);
        connect(action, &QPushButton::clicked, this, &MainWindow::actionClicked);

        ++i;
    }

}

void MainWindow::swindleAction()
{
    ui->textBrowser_2->clear();
    ui->textBrowser_2->setText("The swindle command adds good rep to an agent and in turn to its player as well. The chance of"
                               "this dice roll succeeding is decent.");
}

void MainWindow::killAction()
{
    ui->textBrowser_2->clear();
    ui->textBrowser_2->setText("By killing an adjacent agent the agent (and in turn its player) will gain all its rep. The chance"
                               " of this dice roll being succesful is low. A dead agent returns to its deck and"
                               " can be used again after a cooldown.");
}

void MainWindow::actionClicked()
{
    auto button = qobject_cast<QPushButton *>(sender());

//    activeAgent_->getButton()->hide();
    QGraphicsProxyWidget* proxy = activeAgent_->getButton()->graphicsProxyWidget();

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

    // Notify card played
    for (auto card : game_->currentPlayer()->cards()) {
        auto agent = std::dynamic_pointer_cast<Agent>(card)->getButton();
        if (agent == button) {
            game_->currentPlayer()->playCard(card);
        }
    }

    emit waitForReady();

    activeAgent_->getButton()->show();
}

void MainWindow::nextPlayer()
{
    // Disables "previous players" buttons
    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        button->setEnabled(false);
    }

    game_->nextPlayer();
    currentPlayer_ = game_->currentPlayer();

    // Enables next players buttons
    for (auto card : game_->currentPlayer()->cards()) {
        auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
        button->setEnabled(true);
    }

    ui->textBrowser_2->clear();
    ui->textBrowser_2->setText("The points of the current player among with some other status stuff:"
                               " (a method should print this stuff out whenever the context browser isn't busy");

    showCardsInHand();
    clearScene(scene_actions);

    turn_++;
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
    // Creating scenes to store items for example buttons for Agents
    scene_1 = new QGraphicsScene(ui->graphicsView);
    scene_2 = new QGraphicsScene(ui->graphicsView_2);
    scene_3 = new QGraphicsScene(ui->graphicsView_3);
    scene_4 = new QGraphicsScene(ui->graphicsView_4);
    scene_actions = new QGraphicsScene(ui->graphicsView_actions);
    scene_hand = new QGraphicsScene(ui->graphicsView_hand);


    ui->graphicsView->setScene(scene_1);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView_2->setAlignment(Qt::AlignCenter);
    ui->graphicsView_3->setScene(scene_3);
    ui->graphicsView_3->setAlignment(Qt::AlignCenter);
    ui->graphicsView_4->setScene(scene_4);
    ui->graphicsView_4->setAlignment(Qt::AlignCenter);
    ui->graphicsView_actions->setScene(scene_actions);
    ui->graphicsView_actions->setAlignment(Qt::AlignTop);

    ui->graphicsView_hand->setScene(scene_hand);
}

void MainWindow::updateScenes()
{
    std::vector<QGraphicsScene*> scenes = {scene_1, scene_2, scene_3, scene_4};
    for (QGraphicsScene* scene : scenes){
        int i = 0;
        for (auto item : scene->items(Qt::AscendingOrder)) {
            item->setPos((CARD_WIDTH + PADDING_X) * i, 20);
            ++i;
        }
    }
}


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

void MainWindow::waitForReady()
{
    clearScene(scene_actions);
    QPushButton* readyButton = new QPushButton("Ready");
    readyButton->resize(ACTION_WIDTH, ACTION_HEIGHT);
    scene_actions->addWidget(readyButton);

    // Disables all buttons so Ready is the only thing you can press
    for (auto player : game_->players()) {
        for (auto card : player->cards()) {
            auto button = std::dynamic_pointer_cast<Agent>(card)->getButton();
            button->setEnabled(false);
        }
    }

    ui->textBrowser_2->setText(READY_TEXT);
    connect(readyButton, &QAbstractButton::clicked, this, &MainWindow::nextPlayer);
}

void MainWindow::clearScene(QGraphicsScene* scene)
{
  for (auto item : scene->items()) {
      item->setVisible(false);
  }
}
