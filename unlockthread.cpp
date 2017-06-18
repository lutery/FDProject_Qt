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
    QObject::connect(&fdObject, SIGNAL(onUnlock(bool)), this, SIGNAL(onUnlock(bool)));
    qDebug() << "start unlock";
    fdObject.sltUnlockHandle(this->mFilePath);
    qDebug() << "end unlock";
}
