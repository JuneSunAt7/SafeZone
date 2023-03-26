#ifndef QAV_H
#define QAV_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QPair>


#include "mainwindow.h"

class QAv : public QObject{
   void startCheck(const QString &fName);

 private:
    QMap<QString,QString >avs;
    QList<QString> results;
    QString fileName;
     QAvProcess* createProcess();
    QByteArray parseOutput(const QString &avName,const QString &output);

signals:
    void onAVDone(const QString avName,
    const QString avResult);
private slots:
    void onAvFinished(QAvProcess *sender,
    const QString &av,
    const QString &output, const int exitCode);
};

#endif // QAV_H
