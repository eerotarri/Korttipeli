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

    ui->player3NameInput->setEnabled(false);
    ui->player4NameInput->setEnabled(false);
    ui->playerAmountSpinBox->setValue(2);
    ui->playerAmountSpinBox->setMinimum(2);

    // Default values for player names
    ui->player1NameInput->setText("Player 1");
    ui->player2NameInput->setText("Player 2");


    connect(ui->playerAmountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigurationWindow::amountOfPlayersChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConfigurationWindow::okPressed);


}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::amountOfPlayersChanged(int)
{
    switch (ui->playerAmountSpinBox->value()) {
        case 2:
            ui->player3NameInput->setEnabled(false);
            ui->player4NameInput->setEnabled(false);
            ui->player3NameInput->clear();
            ui->player4NameInput->clear();
            break;
        case 3:
            ui->player3NameInput->setEnabled(true);
            ui->player4NameInput->setEnabled(false);
            ui->player4NameInput->clear();
            break;
        case 4:
            ui->player3NameInput->setEnabled(true);
            ui->player4NameInput->setEnabled(true);
            break;
    }
}

void ConfigurationWindow::okPressed()
{
    QString player1 = ui->player1NameInput->text();
    g_->addPlayer(player1);
    QString player2 = ui->player2NameInput->text();
    g_->addPlayer(player2);

    if (ui->playerAmountSpinBox->value() == 3) {
        QString player3 = ui->player3NameInput->text();
        g_->addPlayer(player3);
    } else if (ui->playerAmountSpinBox->value() == 4) {
        QString player3 = ui->player3NameInput->text();
        g_->addPlayer(player3);
        QString player4 = ui->player4NameInput->text();
        g_->addPlayer(player4);
    }
}
