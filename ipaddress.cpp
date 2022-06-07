#include "ipaddress.h"

IPAddress::IPAddress(QObject *parent) : QObject(parent){

}

IPAddress::IPAddress(const QString &ipaddrPrefix, QObject *parent) : QObject(parent){
    setAddress(ipaddrPrefix);
}

IPAddress::IPAddress(const QString &ipaddr, const QString &mask, QObject *parent) : QObject(parent){
    setAddress(ipaddr, mask);
}

void IPAddress::setAddress(const QString &ipaddrPrefix){
    QStringList addrPrefix = ipaddrPrefix.split("/");
    if(isValidAddress(addrPrefix[0]) == true && VALID_PREFIX(addrPrefix[1].toUInt())){
        address = addrPrefix[0];
        netmask = NETMASK[addrPrefix[1].toUInt()];
    }
}

void IPAddress::setAddress(const QString &ipaddr, const QString &mask){
    if(isValidAddress(ipaddr) == true && isValidAddress(mask) == true){
        address = ipaddr;
        netmask = mask;
    }
}

QStringList IPAddress::hosts(){
    QHostAddress addr(minAddressHost());
    quint64 num = countHosts();
    listHosts.clear();
    for(quint64 index = 0; index < num; index++)
        listHosts.append(QHostAddress(addr.toIPv4Address() + index).toString());
    return listHosts;
}

QStringList IPAddress::addresses(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        QHostAddress addr(networkAddress());
        quint64 num = countAddress();
        listHosts.clear();
        for(quint64 index = 0; index < num; index++)
            listHosts.append(QHostAddress(addr.toIPv4Address() + index).toString());
        return listHosts;
    }
    return QStringList();
}


QString IPAddress::addressClass(){
    if(isValidAddress(address) == true){
        quint32 addr = address.split(".")[0].toUInt();
        if(addr >= 0 && addr <= 127)
            return QString("A");
        else if(addr >= 128 && addr <= 191)
            return QString("B");
        else if(addr >= 192 && addr <= 223)
            return QString("C");
        else if(addr >= 224 && addr <= 239)
            return QString("D");
        else if(addr >= 240 && addr <= 255)
            return QString("E");
    }
    return QString();
}

QStringList IPAddress::subnets(quint8 bit){
    QStringList listSubnet;
    quint32 bits = 32;
    quint8 prefix = 0;
    quint64 numSubnet = 0;
    QHostAddress addr(address);
    QHostAddress mask(netmask);
    prefix = maskToPrefix(netmask);
    prefix += bit;
    if(VALID_PREFIX(prefix)){
        bits -= prefix;
        numSubnet = qPow(2, bit);
        for(quint32 index = 0; index < numSubnet; index++)
            listSubnet.append(QString("%1/%2").arg(QHostAddress((addr.toIPv4Address() & mask.toIPv4Address()) | (index << bits)).toString()).arg(prefix));
        return listSubnet;
    }
    return QStringList();
}

QString IPAddress::wildMask(){
    if(isValidAddress(netmask) == true){
        QHostAddress mask(netmask);
        return QHostAddress(~mask.toIPv4Address()).toString();
    }
    return QString();
}

qint32 IPAddress::maskToPrefix(const QString &mask){
    quint32 index = 0;
    for(index = 0; index < NETMASK.size(); index++)
        if(NETMASK[index] == mask)
            return index;
    return EOF;
}

bool IPAddress::isValidAddress(const QString &address){
    QString ipMask = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression ipRegex ("^" + ipMask + "(\\." + ipMask + ")?" + "(\\." + ipMask + ")?" + "(\\." + ipMask + ")?$");
    QRegularExpressionMatch match = ipRegex.match(address);
    return match.hasMatch();
}

quint64 IPAddress::countHosts(){
    if( isValidAddress(netmask) == true){
        if(maskToPrefix(netmask) == 31){
            numHosts = qPow(2, (32 - maskToPrefix(netmask)));
            return numHosts;
        }
        else if(maskToPrefix(netmask) < 31){
            numHosts = qPow(2, (32 - maskToPrefix(netmask))) - 2;
            return numHosts;
        }
    }
    return 0;
}

quint64 IPAddress::countAddress(){
    if(isValidAddress(netmask) == true){
        numAddress = qPow(2, (32 - maskToPrefix(netmask)));
        return numAddress;
    }
    return 0;
}

QString IPAddress::networkAddress(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        QHostAddress addr(address);
        QHostAddress mask(netmask);
        network = QHostAddress(addr.toIPv4Address() & mask.toIPv4Address()).toString();
        return network;
    }
    return QString();
}

QString IPAddress::networkBroadcast(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        QHostAddress addr(address);
        QHostAddress mask(netmask);
        broadcast = QHostAddress((addr.toIPv4Address() & mask.toIPv4Address()) | ~mask.toIPv4Address()).toString();
        return broadcast;
    }
    return QString();
}

QString IPAddress::minAddressHost(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        QHostAddress addr(address);
        QHostAddress mask(netmask);
        if(netmask == "255.255.255.255")
            minHost = address;
        else if(netmask == "255.255.255.254")
            minHost = QHostAddress((addr.toIPv4Address() & mask.toIPv4Address())).toString();
        else
            minHost = QHostAddress((addr.toIPv4Address() & mask.toIPv4Address()) + 1).toString();
        return minHost;
    }
    return QString();
}

QString IPAddress::maxAddressHost(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        QHostAddress addr(address);
        QHostAddress mask(netmask);
        if(netmask == "255.255.255.255")
            minHost = address;
        else if(netmask == "255.255.255.254")
            maxHost = QHostAddress((addr.toIPv4Address() & mask.toIPv4Address()) + 1).toString();
        else
            maxHost = QHostAddress((addr.toIPv4Address() & mask.toIPv4Address()) | (~mask.toIPv4Address() - 1)).toString();
        return maxHost;
    }
    return QString();
}
