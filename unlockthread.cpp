#include "unlockthread.h"
#include "fdobject.h"
#include <QDebug>

UnlockThread::UnlockThread(QString filePath, QObject *parent) : QThread(parent)
{
    this->mFilePath = filePath;
}

void UnlockThread::run()
{
    FDObject fdObject;
//    QObject::connect(&fdObject, SIGNAL())
    qDebug() << "start unlock";
    fdObject.unlockHandle(this->mFilePath);
    qDebug() << "end unlock";
}