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
    void nextPlayer();
    void swindleAction();
    void killAction();
    //void Ass();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Interface::Game> game_;

    std::shared_ptr<Interface::Player> currentPlayer_;

    std::map<QString, std::vector<QPushButton*>> playerCards_;

    std::shared_ptr<Agent> activeAgent_;

    QGraphicsScene* scene_1;
    QGraphicsScene* scene_2;
    QGraphicsScene* scene_3;
    QGraphicsScene* scene_4;
    QGraphicsScene* scene_actions;
    QGraphicsScene* scene_hand;


    std::vector<QColor> colors_ = {QColor(255,0,118), QColor(225,0,0), QColor(203,80,80), QColor(80,196,203), QColor(12,83,88),
                                  QColor(27,88,12), QColor(223,151,78), QColor(78,112,223), QColor(151,78,223), QColor(187,235,124),
                                  QColor(255,200,30), QColor(154,255,0)};

    void initializeLocations();
    void setupUserInterface();
    void updateScenes();
    void updateHand();
};

#endif // MAINWINDOW_HH
