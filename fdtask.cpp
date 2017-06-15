#include "fdtask.h"

FDTask::FDTask(QObject *parent) : QObject(parent)
{

}

FDTask::~FDTask()
{

}

int FDTask::getTaskID()
{
    return this->mTaskID;
}

void FDTask::setTaskID(int taskid)
{
    this->mTaskID = taskid;
}
