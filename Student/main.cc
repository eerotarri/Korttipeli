#include <QApplication>
#include <simplemainwindow.hh>

#include "mainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(default_assets);

    MainWindow w;
    w.show();

    return a.exec();
}
