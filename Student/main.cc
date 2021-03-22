#include <QApplication>
#include <simplemainwindow.hh>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleMainWindow w;
    w.show();

    return a.exec();
}
