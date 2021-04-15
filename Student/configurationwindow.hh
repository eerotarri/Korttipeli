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

class ConfigurationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationWindow(QWidget *parent = nullptr, std::shared_ptr<Interface::Game> game = nullptr);
    ~ConfigurationWindow();

signals:
    void valueChanged(int);

public slots:
    void amountOfPlayersChanged(int);
    void okPressed();

private:
    Ui::ConfigurationWindow *ui;
    std::vector<std::shared_ptr<Player> > players__;

    std::shared_ptr<Interface::Game> g_;
};

#endif // CONFIGURATIONWINDOW_HH
