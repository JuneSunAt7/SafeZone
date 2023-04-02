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
#include <QSysInfo>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCursor cursor( ui->textEdit->textCursor() );
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->progressBar->setStyleSheet("border-radius:20px;"
                                   "font: 700 22pt 'Segoe UI';"
                                   "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 254, 209, 255), stop:1 rgba(0, 172, 234, 255));"
                                   "selection-background-color: blue;");
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool virus = false;

    QDirIterator itDirs(ui->lineEdit->text(), QDir::Dirs );
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
                    ui->progressBar->setVisible(true);
                    ui->progressBar->setValue(i);
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
          ui->progressBar->setVisible(false);
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
    QString filename = QDateTime::currentDateTime().toString("ddMMyyyy HHmmss") + "safe_zone_repo.szr";

   QFile *report = new QFile(filename);
   report->open(QFile::WriteOnly);
   QString data;
   QSysInfo info;
   data.append("SYSTEM\n");

   data.append(   "Build CPU architecture: "+info.buildCpuArchitecture() + "\n" +
            "Kernel: " + info.kernelType() + info.kernelVersion() + "\n" +
            "Machine Unique id: "  + info.machineUniqueId() + "\n" +
            "Product: " + info.prettyProductName() + " " + info.productType() + " " + info.productVersion() + "\n");

   data.append("OPENED PORTS\n");

   QString program = "netstat -a";

   QProcess *Process = new QProcess(this);
   Process->start(program);
   Process->waitForFinished();
   QString output = Process->readAll();
   output.remove("\r\n\xEF\xBF\xBD\xEF\xBF\xBD\xE2\xA8\xA2\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xE7\xA5\xAD\xEF\xBF\xBD\xEF\xBF\xBD\r\n\r\n  \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD    \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD        \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xE8\xAD\xA8\xEF\xBF\xBD \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD          \xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xAD\xA8\xEF\xBF\xBD\r\n");


   data.append(output);


   report->write(data.toUtf8());


   report->close();

   delete report;

   ui->textEdit->setPlainText("Report saved as " + filename + "\n" + "You can open with notepad.");

}


void MainWindow::on_fullCheckBth_clicked()
{
    QString text;
    QString consister = ""; //read from signature txt and consist every str with readable file
    QStringList conOut;
    QFile *sign = new QFile("sign1.txt");

    sign->open(QFile::ReadOnly);
    while (!sign->atEnd()) {
        conOut.append(sign->readLine());
    }
    sign->close();


    QDirIterator it(ui->lineEdit->text(),  QDir::NoFilter, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFile f(it.next());
        f.open(QIODevice::ReadOnly);

        for(int i = 0; i < conOut.size(); i++){ // read all str and consist with hex-file
                ui->progressBar->setVisible(true);
                ui->progressBar->setValue(i);
         if(f.readLine().toHex() == conOut.at(i)){
             text.append("          " +f.fileName() +"   -- virus!!    \n" );
             qDebug() << "          " +f.fileName() +"   -- virus!!    \n";

         }

        }
        f.close();
    }
        ui->progressBar->setVisible(false);
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


void MainWindow::on_settingsBth_clicked()
{

}


void MainWindow::on_sysBth_clicked()
{
    QSysInfo info;
    QString data;

    data = "Build CPU architecture: "+info.buildCpuArchitecture() + "\n" +
            "Kernel: " + info.kernelType() + info.kernelVersion() + "\n" +
            "Machine Unique id: "  + info.machineUniqueId() + "\n" +
            "Product: " + info.prettyProductName() + " " + info.productType() + " " + info.productVersion();

    ui->textEdit->setPlainText(data);
}


void MainWindow::on_vulnsBth_clicked()
{

}

