#include "ip.h"
#include <QTextStream>
#include <QtGlobal>
#include <QVector>


IP::IP(QString raw_ip): ip(0x0) {
    quint8 ip0 = static_cast<quint8>(raw_ip.section('.', 0, 0).toUInt());
    quint8 ip1 = static_cast<quint8>(raw_ip.section('.', 1, 1).toUInt());
    quint8 ip2 = static_cast<quint8>(raw_ip.section('.', 2, 2).toUInt());
    quint8 ip3 = static_cast<quint8>(raw_ip.section('.', 3, 3).toUInt());
    ip = ip3 + (ip2 << 8) + (ip1 << 16) + (ip0 << 24);
}

IP::IP(quint32 raw_ip): ip(raw_ip) {};

QString IP::toString() const {
    QString IPString;
    QTextStream strIP(&IPString);
    quint32 tmp = ip;
    QVector<quint8> v;

    for (int i = 0; i < 4; ++i) {
        quint8 ip_section = static_cast<quint8>(tmp % 256);
        v.push_back(ip_section);
        tmp = (tmp >> 8);
    }

    for (int i = 3; i > 0; --i) {
        strIP << v[i] << ".";
    }

    strIP << v[0];

    return IPString;
}

QString IP::toHex() const {
    QString IPHex;
    QTextStream hexIP(&IPHex);
    hexIP.setIntegerBase(16);
    hexIP << ip;
    return IPHex;
}

IP operator+(const IP &lip, const quint32 addition) {
    IP ip(lip.ip + addition);
    return ip;
}

bool operator==(const IP &lip, const IP &rip) {
    return lip.ip == rip.ip;
}

IP &IP::operator++() {
    ++ip;
    return *this;
}
