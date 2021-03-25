#ifndef CONFIGURATIONWINDOW_HH
#define CONFIGURATIONWINDOW_HH

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
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    ~ConfigurationWindow();

signals:
    void valueChanged(int);

public slots:
    void amountOfPlayersChanged(int);
    void okPressed();

private:
    Ui::ConfigurationWindow *ui;
    std::vector<std::shared_ptr<Player> > players__;
};

#endif // CONFIGURATIONWINDOW_HH
