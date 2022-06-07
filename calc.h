#ifndef CALC_H
#define CALC_H

#include <QWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include<QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

#include "ipaddress.h"

class Calc : public QWidget{

    Q_OBJECT

public:
    Calc(QWidget *parent = nullptr);
    virtual ~Calc(){}

private:
    QComboBox *listMask = nullptr;
    QLineEdit *ipAddr = nullptr;
    QLineEdit *address = nullptr;
    QLineEdit *netmask = nullptr;
    QLineEdit *wildNetMask = nullptr;
    QLineEdit *broadcast = nullptr;
    QLineEdit *network = nullptr;
    QLineEdit *maxhost = nullptr;
    QLineEdit *minhost = nullptr;
    QLineEdit *bitmask = nullptr;
    QLineEdit *hosts = nullptr;
    QLineEdit *addresses = nullptr;
    QLineEdit *addrClass = nullptr;
    QLabel *labAddr = nullptr;
    QLabel *labAddress = nullptr;
    QLabel *labNetmask = nullptr;
    QLabel *labWildMask = nullptr;
    QLabel *labBroadcast = nullptr;
    QLabel *labNetwork = nullptr;
    QLabel *labMinhost = nullptr;
    QLabel *labMaxhost = nullptr;
    QLabel *labBitmask = nullptr;
    QLabel *labHosts = nullptr;
    QLabel *labAddresses = nullptr;
    QLabel *labAddrClass = nullptr;
    QPushButton *btnResult = nullptr;
    QGridLayout *layout = nullptr;
    QHBoxLayout *hlayout = nullptr;
    QHBoxLayout *hlayout2 = nullptr;
    QVBoxLayout *vlayout = nullptr;
    IPAddress *addr = nullptr;
    QTextEdit *textEdit = nullptr;
    QLineEdit *bits = nullptr;
    QLabel *labBits = nullptr;
    QStringList headerName = {"Name", "Value", "Hex", "Bin"};    
    QString ipMask = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpressionValidator *ipValid = nullptr;

private slots:
    void getResult();
};
#endif // CALC_H
