#include "curshfilethread.h"
#include "fdobject.h"
#include <QDebug>

CurshFileThread::CurshFileThread(QString filePath, QObject *parent) : QThread(parent)
{
    this->mFilePath = filePath;
}

void CurshFileThread::run()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(onCurshFile(bool)), this, SIGNAL(onCurshFile(bool)));
    qDebug() << "start cursh file";
    fdObject.sltCrushFile(this->mFilePath);
    qDebug() << "end cursh file";
}
