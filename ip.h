#ifndef IP_H
#define IP_H

#include <QtGlobal>
#include <QString>

class IP
{
friend IP operator+(const IP &, const quint32);
friend bool operator==(const IP &lip, const IP &rip);
friend bool operator<(const IP &lip, const IP &rip);
friend bool operator<=(const IP &lip, const IP &rip);

private:
    quint32 ip;

public:
using port = quint32;

public:
    IP(){};
    IP(QString raw_ip);
    IP(quint32);

    QString toString() const;

    QString toHex() const;

    IP &operator++();
};


struct Address {
    IP ip;
    IP::port port;
};



#endif // IP_H
