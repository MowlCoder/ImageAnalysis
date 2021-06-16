#include "mainwindow.h"
#include "BinParse.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    BinParse* bp = new BinParse("dump1.bin");

    bp->Parse();
    bp->PrintImageMatrix();

    return a.exec();
}
