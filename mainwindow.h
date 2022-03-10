#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scanner.h"
#include "ip.h"
#include <QFutureWatcher>
#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QFutureWatcher<ScannerResult> watcher;

private slots:
    void on_actionquit_triggered();
    void resultReady(int index);
    void on_scanStart_clicked();

private:
    Ui::MainWindow *ui;
    void writeOut(ScannerResult res);
};
#endif // MAINWINDOW_H
