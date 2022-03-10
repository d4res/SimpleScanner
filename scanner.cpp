#include "scanner.h"
#include <QTcpSocket>

ScannerResult Scanner::scan(const Address addr)
{
    IP ip = addr.ip;
    IP::port port = addr.port;
    QTcpSocket sock;
    sock.connectToHost(ip.toString(), port);
    ScannerResult result;
    result.addr = addr;
    if (!sock.waitForConnected(3)) {
        result.isOpen = false;
        result.msg = sock.errorString();
        sock.close();
        return result;
    }
    else {
        result.isOpen = true;
        result.msg = "";
        sock.close();
        return result;
    }

}

Scanner::Scanner()
{

}

void Scanner::start(IP ipStart, IP::port portStart, IP ipEnd, IP::port portEnd)
{
    QList<Address> list;
    for (IP ip = ipStart; ip <= ipEnd; ++ip) {
        for (IP::port port = portStart; port <= portEnd; ++port) {
            Address addr = {ip, port};
            list.append(addr);
        }
    }
    result =  QtConcurrent::mapped(QThreadPool::globalInstance(),list, Scanner::scan);
}
