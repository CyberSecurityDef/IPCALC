#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setMaximumSize(MAX_WIDTH, MAX_HEIGHT);
    setMinimumSize(MAX_WIDTH, MAX_HEIGHT);

    center = new QTabWidget(this);
    setCentralWidget(center);

    calc = new Calc(this);
    center->addTab(calc, tr("Calc"));
}

MainWindow::~MainWindow(){

}



