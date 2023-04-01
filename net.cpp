#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QFile>
#include <QDebug>
#include <QDirIterator>
#include <QDateTime>
#include <QTcpSocket>
#include <QHostAddress>
#include <QScrollBar>
#include <QTextCodec>
#include <QNetworkInterface>


void MainWindow::on_scanPortsBth_clicked()
{


    QString program = "netstat -a";

    QProcess *Process = new QProcess(this);
    Process->start(program);
    Process->waitForFinished();
    QString output = Process->readAll();
    output.remove("\r\n\xEF\xBF\xBD\xEF\xBF\xBD\xE2\xA8\xA2\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xE7\xA5\xAD\xEF\xBF\xBD\xEF\xBF\xBD\r\n\r\n  \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD    \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD        \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xE8\xAD\xA8\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD          \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xAD\xA8\xEF\xBF\xBD\r\n");
    ui->textEdit->setText(output);

    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);

     QScrollBar *bar = ui->textEdit->verticalScrollBar();
     bar->setValue(bar->maximum());

}

void MainWindow::on_netBth_clicked()
{
     QNetworkInterface interface;
    QList <QNetworkInterface> list = interface.allInterfaces();

    QString result;
    for (int i = 0; i < list.size(); ++i)
    {
        result += list.at(i).hardwareAddress() + list.at(i).humanReadableName() + list.at(i).flags() +
                list.at(i).name() + QString("\n");

    }
    ui->textEdit->setPlainText(result);

    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);

     QScrollBar *bar = ui->textEdit->verticalScrollBar();
     bar->setValue(bar->maximum());
}
