#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>

#include "calc.h"

#define MAX_HEIGHT 600
#define MAX_WIDTH 800

class MainWindow : public QMainWindow{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:    
    QTabWidget *center = nullptr;
    Calc *calc = nullptr;   
    QVBoxLayout *layout = nullptr;
};
#endif // MAINWINDOW_H
