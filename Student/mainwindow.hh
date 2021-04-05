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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCardDimensions(int width, int height, int padding_x, int padding_y);

    void addCardToPlayer(std::shared_ptr<Interface::Player>);
    void showCardsInHand();


public slots:
    void agentClicked();
    void moveAction();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Interface::Game> game_;

    std::shared_ptr<Interface::Player> currentPlayer_;

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
