#include "curshfiletask.h"
#include "fdtask.h"
#include "fdobject.h"
#include <QDebug>

CurshFileTask::CurshFileTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

CurshFileTask::~CurshFileTask()
{

}

void CurshFileTask::execTask()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(sigCurshFile(bool)), this, SIGNAL(sigCurshFile(bool)));
    fdObject.sltCrushFile(this->mFilePath);
}
