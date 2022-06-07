#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QObject>
#include <QHostAddress>
#include <QRegularExpression>

#define VALID_PREFIX(x) (x >= 0 && x <= 32)

class IPAddress : public QObject{

    Q_OBJECT

public:
    IPAddress(QObject *parent = nullptr);    
    IPAddress(const QString &ipaddrPrefix, QObject *parent = nullptr);
    IPAddress(const QString &ipaddr, const QString &mask, QObject *parent = nullptr);

    virtual ~IPAddress(){}

    void setAddress(const QString &ipaddrPrefix);
    void setAddress(const QString &ipaddr, const QString &mask);

    quint64 countHosts();
    quint64 countAddress();

    QString networkAddress();
    QString networkBroadcast();

    QString minAddressHost();
    QString maxAddressHost();

    QStringList hosts();
    QStringList addresses();

    QStringList listAllNetMask() const{ return NETMASK; }
    QString wildMask();

    QString addressClass();

    QStringList subnets(quint8 bit = 1);

    qint32 maskToPrefix(const QString &mask);
    QString prefixToMask(uint32_t prefix) const{ return NETMASK[prefix]; }

    bool isValidAddress(const QString &address);

private:
    QString network;
    QString broadcast;
    QString minHost;
    QString maxHost;
    QStringList listHosts;
    QStringList listAddresses;
    quint64 numHosts = 0;
    quint64 numAddress = 0;
    QString address;
    QString netmask;
    const QStringList NETMASK = {"0.0.0.0",
                                  "128.0.0.0",
                                  "192.0.0.0",
                                  "224.0.0.0",
                                  "240.0.0.0",
                                  "248.0.0.0",
                                  "252.0.0.0",
                                  "254.0.0.0",
                                  "255.0.0.0",
                                  "255.128.0.0",
                                  "255.192.0.0",
                                  "255.224.0.0",
                                  "255.240.0.0",
                                  "255.248.0.0",
                                  "255.252.0.0",
                                  "255.254.0.0",
                                  "255.255.0.0",
                                  "255.255.128.0",
                                  "255.255.192.0",
                                  "255.255.224.0",
                                  "255.255.240.0",
                                  "255.255.248.0",
                                  "255.255.252.0",
                                  "255.255.254.0",
                                  "255.255.255.0",
                                  "255.255.255.128",
                                  "255.255.255.192",
                                  "255.255.255.224",
                                  "255.255.255.240",
                                  "255.255.255.248",
                                  "255.255.255.252",
                                  "255.255.255.254",
                                  "255.255.255.255"};
};

#endif // IPADDRESS_H
