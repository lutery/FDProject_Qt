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
    fdObject.sltUnlockHandle(this->mFilePath);
}
