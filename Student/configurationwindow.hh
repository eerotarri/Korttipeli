#ifndef CONFIGURATIONWINDOW_HH
#define CONFIGURATIONWINDOW_HH

#include "mainwindow.hh"

#include <QDialog>
#include <QSpinBox>
#include <vector>

namespace Ui {
class ConfigurationWindow;
}

class Player;
/**
 * @brief The ConfigurationWindow luokka
 * Tämä luokka piirtää konfiguraatioikkunan, josta saadaan pelaajien nimet.
 */
class ConfigurationWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ConfigurationWindow rakentaja
     * @pre Game instanssi on alustettu
     * @param game
     */
    explicit ConfigurationWindow(QWidget *parent = nullptr, std::shared_ptr<Interface::Game> game = nullptr);
    ~ConfigurationWindow();

signals:
    void valueChanged(int);

public slots:
    /**
     * @brief Muuttaa pelaajien määrää välillä 2-4
     *
     * Muuttaa laatikkoja koskemattomiksi tarpeen mukaan
     */
    void amountOfPlayersChanged(int);
    /**
     * @brief Lisää pelaajat gameen riippuen pelaajamäärästä.
     */
    void okPressed();

private:
    Ui::ConfigurationWindow *ui;
    std::vector<std::shared_ptr<Player> > players__;

    std::shared_ptr<Interface::Game> g_;
};

#endif // CONFIGURATIONWINDOW_HH
