#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <memory>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>

#include "cardinterface.h"
#include "simplecarditem.hh"
#include "game.h"
#include "map"

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

    void setCardDimensions(int width, int height, int padding_x, int padding_y);

    void addCardToPlayer();
    void showCardsInHand();
    void clearScene(QGraphicsScene* scene);

public slots:
    void agentClicked();
    void moveAction();
    void actionClicked();
    //void Ass();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Interface::Game> game_;

    std::shared_ptr<Interface::Player> currentPlayer_;

    std::map<QString, std::vector<QPushButton*>> playerCards_;

    Agent* activeAgent_;

    QGraphicsScene* scene_1;
    QGraphicsScene* scene_2;
    QGraphicsScene* scene_3;
    QGraphicsScene* scene_4;
    QGraphicsScene* scene_actions;
    QGraphicsScene* scene_hand;

    void initializeLocations();
    void setupUserInterface();
    void addPlayers();
};

#endif // MAINWINDOW_HH
