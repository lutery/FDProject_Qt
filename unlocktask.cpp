#include "unlocktask.h"
#include "fdobject.h"

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
    fdObject.sltUnlockHandle(this->mFilePath);
}
