#include "analysistask.h"
#include "fdobject.h"

AnalysisTask::AnalysisTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

void AnalysisTask::execTask()
{
    FDObject fdObject;
    fdObject.analysis(mFilePath);
}
