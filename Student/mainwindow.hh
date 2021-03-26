#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <memory>
#include <QGraphicsScene>

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

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;
};

#endif // MAINWINDOW_HH
