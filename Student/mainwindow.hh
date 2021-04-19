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

/**
 * @brief Pääikkuna luokka
 * Luokka piirtää pääikkunan tarvittavilla metodeilla

 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow luokan rakentaja
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief addCardToPlayer jakaa pelaajille pelissä käytettävät kortit
     */
    void addCardToPlayer();
    /**
     * @brief showCardsInHand näyttää vuorossa olevan pelaajan
     * kädessä olevat kortit
     */
    void showCardsInHand();
    /**
     * @brief clearScene tyhjentää halutun ruudun
     * @param scene joka tyhjennetään
     */
    void clearScene(QGraphicsScene* scene);

    /**
     * @brief Korttien dimensiot ja välien suuruudet
     */
    static const int CARD_WIDTH = 80;
    static const int CARD_HEIGHT = 110;
    static const int PADDING_Y = 20;
    static const int PADDING_X = 7;

    /**
     * @brief Siirtonappien dimensiot
     */
    static const int ACTION_WIDTH = 239;
    static const int ACTION_HEIGHT = 50;

    /**
     * @brief Kuvien dimensiot
     */
    static const int ICON_WIDTH = 40;
    static const int ICON_HEIGHT = 100;

    /**
     * @brief Operaatioiden mahdollisuudet onnistua (kymmenestä)
     */
    static const int KILL_CHANCE = 6;
    static const int SWINDLE_CHANCE = 3;

    /**
     * @brief Pistemäärä, jonka pelaaja tarvitsee voittaakseen
     */
    static const int WINNING_SCORE = 10;

    /**
      * @brief Lista pelikentän sijaintien nimistä
      */
    const std::vector<QString> LOCATIONS = {"Castle", "Marketplace", "Forest", "Slums"};

public slots:
    /**
     * @brief agentClicked tapahtuu agenttikorttia klikatessa
     * @post piirtää operaatiot
     */
    void agentClicked();
    /**
     * @brief moveAction tapahtuu liikkumiseen johtavaa nappia
     * @post piirtää napit, mihin sijaintiin pelaaja haluaa liikuttaa agentin
     */
    void moveAction();
    /**
     * @brief actionClicked tapahtuu sijainnin valitsemisesta
     * @post agentti on siirtynyt toiseen sijaintiin
     */
    void actionClicked();
    /**
     * @brief nextPlayer siirtää vuorossa olevan pelaajan seuraavaan
     * @post vuorossa on seuraava pelaaja
     */
    void nextPlayer();
    /**
     * @brief swindleAction toteuttaa pääikkunassa huijaamisoperaation
     * @post agentti saa lisää vaikutusvaltaa, jos operaatio onnistuu
     */
    void swindleAction();
    /**
     * @brief killAction toteuttaa pääikkunassa tappamisoperaation
     * @post agentti saa vastustajan tapetun agentin vaikutusvallan
     * ja vastustajan agentti palaa käteen, jos operaatio onnistuu
     */
    void killAction();
    /**
     * @brief getSceneItemSize palauttaa halutussa ruudussa olevien agenttien määrän
     * @param scene_id haluttu ruutu
     * @return agenttien määrä ruudussa
     */
    unsigned int getSceneItemSize(unsigned int scene_id);
    /**
     * @brief endGame päättää pelin, kun joku pelaajista on voittanut
     * @post peli on päättynyt ja pelin voi sulkea
     */
    void endGame();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Interface::Game> game_;
    std::shared_ptr<Interface::Runner> runner_;

    std::shared_ptr<Interface::Player> currentPlayer_;
    std::shared_ptr<Interface::Player> winner_ = nullptr;


    std::map<QString, std::vector<QPushButton*>> playerCards_;

    std::shared_ptr<Agent> activeAgent_;

    bool agent_moved_ = false;

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
    unsigned short getRandom();

};

#endif // MAINWINDOW_HH
