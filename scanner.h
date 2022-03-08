#ifndef SCANNER_H
#define SCANNER_H

#include "ip.h"
#include <QThread>
#include <QThreadPool>
#include <QtConcurrent>
#include <QFuture>

struct ScannerResult {
    Address addr;
    bool isOpen;
    QString msg;
};


class Scanner
{
private:
    static ScannerResult scan(Address addr);


public:
    QFuture<ScannerResult> result;
    bool started;
    Scanner();
    void start(IP ipStart, IP::port portStart, IP ipEnd, IP::port portEnd);
};


#endif // SCANNER_H
