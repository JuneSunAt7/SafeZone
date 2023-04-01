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
    QStringList conOut;
    QFile *sign = new QFile("sign1.txt");

    sign->open(QFile::ReadOnly);
    while (!sign->atEnd()) {
        conOut.append(sign->readLine());
    }
    sign->close();



      QDirIterator itFiles(ui->lineEdit->text(), QDir::Files);
      while (itFiles.hasNext()) {
        itFiles.next();
        QFileInfo info = itFiles.fileInfo();
             QFile *reads = new QFile(info.absoluteFilePath());

             reads->open(QFile::ReadOnly);
            for(int i = 0; i < conOut.size(); i++){ // read all str and consist with hex-file
             if(reads->readLine().toHex() == conOut.at(i)){
                 text.append("          " +info.fileName() +"   -- virus!!    \n" );
                 qDebug() << "          " +info.fileName() +"   -- virus!!    \n";

                 virus = true;

             }
             else{

                 virus = false;

             }
            }



             reads->close();
      }
      if(text.size() != 0){

          QColor color = ui->textEdit->textColor();
          ui->textEdit->setTextColor(Qt::red);
           ui->textEdit->setText(text);
          ui->textEdit->setTextColor(color);
      }
      else{
          QColor color = ui->textEdit->textColor();
          ui->textEdit->setTextColor(Qt::green);
          ui->textEdit->setText("Dir clean");
          ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
          ui->textEdit->setTextColor(color);
      }
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

