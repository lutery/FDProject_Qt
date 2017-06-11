#include "fdtask.h"

FDTask::FDTask(QObject *parent) : QObject(parent)
{

}

int FDTask::getTaskID()
{
    return this->mTaskID;
}
