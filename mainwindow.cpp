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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCursor cursor( ui->textEdit->textCursor() );
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool virus = false;

    QDirIterator itDirs(ui->lineEdit->text(), QDir::Dirs);
    QString text;

    QString consister = ""; //read from signature txt and consist every str with readable file

      QDirIterator itFiles(ui->lineEdit->text(), QDir::Files);
      while (itFiles.hasNext()) {
        itFiles.next();
        QFileInfo info = itFiles.fileInfo();
             qDebug() << "D | " << info.fileName() << " |  size" << info.size() << " | " << info.lastModified().toString() << " | ";
             QFile *reads = new QFile(info.absoluteFilePath());

             reads->open(QFile::ReadOnly);

             if(reads->readLine().toHex() == consister){
                 text.append("                               " +info.fileName() +"   -- virus!!    \n" );
                 virus = true;

             }
             else{
                  text.append("                               " +info.fileName() +"  --clean  \n" );
             }


             reads->close();
      }
      ui->textEdit->setText(text);
}




void MainWindow::on_genReportsBth_clicked()
{

}


void MainWindow::on_fullCheckBth_clicked()
{

}


void MainWindow::on_settingsBth_clicked()
{

}


void MainWindow::on_sysBth_clicked()
{

}


void MainWindow::on_vulnsBth_clicked()
{

}

