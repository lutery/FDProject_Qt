#include "analysisthread.h"
#include "fdobject.h"
#include <QDebug>

AnalysisThread::AnalysisThread(QString filePath, QObject *parent) : QThread(parent)
{
    this->mFilePath = filePath;
}

void AnalysisThread::run()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(onComplete(bool,QStringList)), this, SIGNAL(onComplete(bool,QStringList)));
    qDebug() << "start run";
    fdObject.analysis(mFilePath);
    qDebug() << "end run";
}
