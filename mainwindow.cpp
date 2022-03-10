#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextStream>
#include <QTcpSocket>
#include <QString>
#include <QThreadPool>
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


void MainWindow::resultReady(int index)
{
    ScannerResult res = watcher.resultAt(index);
    qDebug() << res.addr.ip.toString() << " "  << res.addr.port << " :" << res.isOpen;
    if (res.isOpen) {

        ui->output->textCursor().insertText(res.addr.ip.toString()
                                             + " "
                                             + QString::number(res.addr.port)
                                             + " "
                                             + "open"
                                             + "\n"
                                             );
    }
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
    int maxThreadCount = ui->threadNum->text().toInt();
    maxThreadCount = maxThreadCount ? maxThreadCount : QThread::idealThreadCount();
    Scanner s;
    QThreadPool::globalInstance()->setMaxThreadCount(maxThreadCount);
    s.start(ipStart, portStart, ipEnd, portEnd);
    watcher.setFuture(s.result);

    QObject::connect(&watcher, SIGNAL(resultReadyAt(int)), this, SLOT(resultReady(int)), Qt::UniqueConnection);


}


void MainWindow::on_scanEnd_clicked()
{
    watcher.future().cancel();
}

