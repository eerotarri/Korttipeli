#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <memory>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QTextBrowser>

#include "cardinterface.h"
#include "simplecarditem.hh"
#include "game.h"
#include "runner.h"
#include "map"
#include "random.h"

namespace Ui {
class MainWindow;
}

class Agent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addCardToPlayer();
    void showCardsInHand();
    void clearScene(QGraphicsScene* scene);

    static const int CARD_WIDTH = 80;
    static const int CARD_HEIGHT = 110;
    static const int PADDING_Y = 20;
    static const int PADDING_X = 7;

    static const int ACTION_WIDTH = 239;
    static const int ACTION_HEIGHT = 50;

    const std::vector<QString> LOCATIONS = {"Castle", "Marketplace", "Forest", "Slums"};

public slots:
    void agentClicked();
    void moveAction();
    void actionClicked();
    void nextPlayer();
    void swindleAction();
    void killAction();
    unsigned int getSceneItemSize(unsigned int scene_id);
    void endGame();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Interface::Game> game_;
    std::shared_ptr<Interface::Runner> runner_;
    std::shared_ptr<Interface::Random> random_;

    std::shared_ptr<Interface::Player> currentPlayer_;
    std::shared_ptr<Interface::Player> winner_;


    std::map<QString, std::vector<QPushButton*>> playerCards_;

    std::shared_ptr<Agent> activeAgent_;

    QGraphicsScene* scene_1;
    QGraphicsScene* scene_2;
    QGraphicsScene* scene_3;
    QGraphicsScene* scene_4;
    QGraphicsScene* scene_actions;
    QGraphicsScene* scene_hand;

    int turn_ = 1;

    std::vector<QColor> colors_ = {QColor(255,0,118), QColor(225,0,0), QColor(203,80,80), QColor(80,196,203), QColor(12,83,88),
                                  QColor(27,88,12), QColor(223,151,78), QColor(78,112,223), QColor(151,78,223), QColor(187,235,124),
                                  QColor(255,200,30), QColor(154,255,0)};


    void initializeLocations();
    void setupUserInterface();
    void updateScenes();
    void updateHand();
    void waitForReady();
    void waitForClose();
    void perform();

};

#endif // MAINWINDOW_HH
