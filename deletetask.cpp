#include "deletetask.h"
#include "fdtask.h"
#include "fdobject.h"
#include <QDebug>

DeleteTask::DeleteTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

DeleteTask::~DeleteTask()
{

}

void DeleteTask::execTask()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(sigDelFile(bool)), this, SIGNAL(sigDelFile(bool)));
    fdObject.sltDeleteFile(mFilePath);
}
