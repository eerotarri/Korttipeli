#include "configurationwindow.hh"
#include "ui_configurationwindow.h"
#include "player.h"
#include "game.h"

#include <QDebug>

ConfigurationWindow::ConfigurationWindow(QWidget *parent, std::shared_ptr<Interface::Game> game) :
    QDialog(parent),
    ui(new Ui::ConfigurationWindow),
    g_(game)
{
    ui->setupUi(this);

    ui->player2NameInput->setEnabled(false);
    ui->player3NameInput->setEnabled(false);
    ui->player4NameInput->setEnabled(false);

    connect(ui->playerAmountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigurationWindow::amountOfPlayersChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConfigurationWindow::okPressed);
//    connect(ui->buttonBox, &QDialogButtonBox::accepted, parent, &MainWindow::getPlayersFromConf);


}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::amountOfPlayersChanged(int)
{
    if (ui->playerAmountSpinBox->value() == 1) {
        ui->player2NameInput->setEnabled(false);
        ui->player3NameInput->setEnabled(false);
        ui->player4NameInput->setEnabled(false);
        ui->player2NameInput->clear();
        ui->player3NameInput->clear();
        ui->player4NameInput->clear();
    } else if (ui->playerAmountSpinBox->value() == 2) {
        ui->player2NameInput->setEnabled(true);
        ui->player3NameInput->setEnabled(false);
        ui->player4NameInput->setEnabled(false);
        ui->player3NameInput->clear();
        ui->player4NameInput->clear();
    } else if (ui->playerAmountSpinBox->value() == 3) {
        ui->player2NameInput->setEnabled(true);
        ui->player3NameInput->setEnabled(true);
        ui->player4NameInput->setEnabled(false);
        ui->player4NameInput->clear();
    }  else {
        ui->player2NameInput->setEnabled(true);
        ui->player3NameInput->setEnabled(true);
        ui->player4NameInput->setEnabled(true);
    }
}

void ConfigurationWindow::okPressed()
{
    QString player1 = ui->player1NameInput->text();
    g_->addPlayer(player1);

    if (ui->playerAmountSpinBox->value() == 2) {
        QString player2 = ui->player2NameInput->text();
        g_->addPlayer(player2);
    } else if (ui->playerAmountSpinBox->value() == 3) {
        QString player2 = ui->player2NameInput->text();
        g_->addPlayer(player2);
        QString player3 = ui->player3NameInput->text();
        g_->addPlayer(player3);
    }  else if (ui->playerAmountSpinBox->value() == 4){
        QString player2 = ui->player2NameInput->text();
        g_->addPlayer(player2);
        QString player3 = ui->player3NameInput->text();
        g_->addPlayer(player3);
        QString player4 = ui->player4NameInput->text();
        g_->addPlayer(player4);
    }
}
