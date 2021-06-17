#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "BinParse.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BinParse* bp = new BinParse("dump1.bin");
    bp->Parse();
    QImage img = bp->GenerateImage();

    ui->label->setPixmap(QPixmap::fromImage(img));

    img.save("object.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

