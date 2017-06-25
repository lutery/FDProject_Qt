#include "unlocktask.h"
#include "fdobject.h"
#include <QDebug>

UnlockTask::UnlockTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

UnlockTask::~UnlockTask()
{

}

void UnlockTask::execTask()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(sigUnlock(bool)), this, SIGNAL(sigUnlook(bool)));
    qDebug() << "start unlock";
    fdObject.sltUnlockHandle(this->mFilePath);
    qDebug() << "end unlock";
}
