#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextStream>
#include <QTcpSocket>
#include <QString>
#include "scanner.h"
#include "ip.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionquit_triggered()
{
    this->close();
}

void MainWindow::on_scanStart_clicked()
{
    QTextStream qout(stdout);

    // attention:
    // when using QBytearray, socket will ignore the \x00,
    // while using the const char*, the socket will end the string with \x00
    IP ipStart(ui->IPStart->text());
    IP ipEnd(ui->IPEnd->text());
    quint16 portStart = ui->portStart->text().toUInt();
    quint16 portEnd = ui->portEnd->text().toUInt();
    ui->output->moveCursor(QTextCursor::Start);
    // basic scan
//    for (quint16 p = portStart; p <= portEnd; ++p) {
//        QTcpSocket sock;
//        sock.connectToHost(ipStart.toString(), p);
//        if (!sock.waitForConnected(3)) qout << sock.errorString();
//        else ui->output->textCursor().insertText("port " + QString::number(p) + " open" + "\n");

//    }
    Scanner s;
    s.start(ipStart, portStart, ipEnd, portEnd);
    s.result.waitForFinished();
    for (auto item : s.result.results()) {
        writeOut(item);
    }

//    QTcpSocket sock;
//    sock.connectToHost("127.0.0.1", 5566);
//    if (!sock.waitForConnected(3)) qout << sock.errorString();

//    ;
//    if (sock.state() == QAbstractSocket::ConnectedState) {
//        const char h[] = "hello";
//        sock.write(h, sizeof(h));
//        sock.waitForBytesWritten();
//    }


}

void MainWindow::writeOut(ScannerResult res)
{
    qDebug() << res.addr.ip.toString() + " "<< res.addr.port << " " << res.isOpen << "\n";
    if (res.isOpen) {
        ui->output->textCursor().insertText("ip "
                                            + res.addr.ip.toString()
                                            + " port "
                                            + QString::number(res.addr.port)
                                            + " open "
                                            + res.msg
                                            + "\n");

    } else {
        qDebug() << "ip " + res.addr.ip.toString()
                    +  " port "
                    + QString::number(res.addr.port)
                    + " close "
                    + res.msg + "\n";
    }

}


