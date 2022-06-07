#include "calc.h"


Calc::Calc(QWidget *parent) : QWidget(parent){
    layout = new QGridLayout();

    labAddr = new QLabel(tr("IP address"), this);
    layout->addWidget(labAddr, 0, 0);
    ipAddr = new QLineEdit(this);
    QRegularExpression ipRegex ("^" + ipMask + "(\\." + ipMask + ")?" + "(\\." + ipMask + ")?" + "(\\." + ipMask + ")?$");
    ipValid = new QRegularExpressionValidator(ipRegex, this);
    ipAddr->setValidator(ipValid);
    layout->addWidget(ipAddr, 0, 1);
    listMask = new QComboBox(this);
    layout->addWidget(listMask, 0, 2);
    btnResult = new QPushButton(tr("Result"), this);
    layout->addWidget(btnResult, 0, 3);

    labBitmask = new QLabel(tr("Bitmask"), this);
    layout->addWidget(labBitmask, 1, 0);
    bitmask = new QLineEdit(this);
    bitmask->setReadOnly(true);
    layout->addWidget(bitmask, 1, 1, 1, 3);

    labAddress = new QLabel(tr("Address"), this);
    layout->addWidget(labAddress,2, 0);
    address = new QLineEdit(this);
    address->setReadOnly(true);
    layout->addWidget(address, 2, 1, 1, 3);

    labNetmask = new QLabel(tr("Netmask"), this);
    layout->addWidget(labNetmask, 3, 0);
    netmask = new QLineEdit(this);
    netmask->setReadOnly(true);
    layout->addWidget(netmask, 3, 1, 1, 3);

    labWildMask = new QLabel(tr("Wildmask"), this);
    layout->addWidget(labWildMask, 4, 0);
    wildNetMask = new QLineEdit(this);
    wildNetMask->setReadOnly(true);
    layout->addWidget(wildNetMask, 4, 1, 1, 3);

    labBroadcast = new QLabel(tr("Broadcast"), this);
    layout->addWidget(labBroadcast, 5, 0);
    broadcast = new QLineEdit(this);
    broadcast->setReadOnly(true);
    layout->addWidget(broadcast, 5, 1, 1, 3);

    labNetwork = new QLabel(tr("Network"), this);
    layout->addWidget(labNetwork, 6, 0);
    network = new QLineEdit(this);
    network->setReadOnly(true);
    layout->addWidget(network, 6, 1, 1, 3);

    labMinhost = new QLabel(tr("Minhost"), this);
    layout->addWidget(labMinhost, 7, 0);
    minhost = new QLineEdit(this);
    minhost->setReadOnly(true);
    layout->addWidget(minhost, 7, 1, 1, 3);

    labMaxhost = new QLabel(tr("Maxhost"), this);
    layout->addWidget(labMaxhost, 8, 0);
    maxhost = new QLineEdit(this);
    maxhost->setReadOnly(true);
    layout->addWidget(maxhost, 8, 1, 1, 3);

    labHosts = new QLabel(tr("Hosts"), this);
    layout->addWidget(labHosts, 9, 0);
    hosts = new QLineEdit(this);
    hosts->setReadOnly(true);
    layout->addWidget(hosts, 9, 1, 1, 3);

    labAddress = new QLabel(tr("Addresses"), this);
    layout->addWidget(labAddress);
    addresses = new QLineEdit(this);
    addresses->setReadOnly(true);
    layout->addWidget(addresses, 10, 1, 1, 3);

    labAddrClass = new QLabel(tr("Class"), this);
    layout->addWidget(labAddrClass);
    addrClass = new QLineEdit(this);
    addrClass->setReadOnly(true);
    layout->addWidget(addrClass, 11, 1, 1, 3);

    hlayout = new QHBoxLayout(this);
    hlayout->addLayout(layout);

    vlayout = new QVBoxLayout();
    hlayout->addLayout(vlayout);

    hlayout2 = new QHBoxLayout();
    vlayout->addLayout(hlayout2);

    hlayout2->addStretch();
    labBits = new QLabel(tr("Bit"), this);
    hlayout2->addWidget(labBits);

    bits = new QLineEdit(this);
    bits->setText("1");
    hlayout2->addWidget(bits);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setPlaceholderText(tr("List subnet"));
    vlayout->addWidget(textEdit);

    addr = new IPAddress(this);
    listMask->addItems(addr->listAllNetMask());

    connect(btnResult, SIGNAL(clicked()), this, SLOT(getResult()));
}

void Calc::getResult(){
    QStringList ls;
    if(!ipAddr->text().isEmpty()){
        QString mask = listMask->currentText();
        addr->setAddress(ipAddr->text(), mask);
        address->setText(ipAddr->text());
        netmask->setText(mask);
        wildNetMask->setText(addr->wildMask());
        broadcast->setText(addr->networkBroadcast());
        network->setText(addr->networkAddress());
        minhost->setText(addr->minAddressHost());
        maxhost->setText(addr->maxAddressHost());
        bitmask->setText(QString::number(addr->maskToPrefix(mask)));
        hosts->setText(QString::number(addr->countHosts()));
        addresses->setText(QString::number(addr->countAddress()));
        addrClass->setText(addr->addressClass());
        ls = addr->subnets(bits->text().toUInt());
        textEdit->clear();
        for(uint32_t index = 0; index < ls.size(); index++)
            textEdit->append(ls[index]);
    }
    else
        QMessageBox::warning(this, nullptr, tr("Enter ip address"));
}
