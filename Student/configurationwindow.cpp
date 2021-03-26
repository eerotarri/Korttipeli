#include "configurationwindow.hh"
#include "ui_configurationwindow.h"
#include "player.h"
#include "game.h"

#include <QDebug>

ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationWindow)
{
    ui->setupUi(this);

    ui->player2NameInput->setEnabled(false);
    ui->player3NameInput->setEnabled(false);
    ui->player4NameInput->setEnabled(false);

    connect(ui->playerAmountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigurationWindow::amountOfPlayersChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConfigurationWindow::okPressed);


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

//    std::shared_ptr<Interface::Player> player1 = std::make_shared<Interface::Player>(g, 1, ui->player1NameInput->text());
//    std::shared_ptr<Interface::Player> player2 = std::make_shared<Interface::Player>(g, 2, ui->player2NameInput->text());
//    g->addPlayer(ui->player1NameInput->text());
//    g->addPlayer(ui->player2NameInput->text());
}
