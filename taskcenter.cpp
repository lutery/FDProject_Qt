#include "taskcenter.h"
#include "fdtask.h"

TaskCenter::TaskCenter(QObject *parent) : QObject(parent)
{
    this->mbRun = true;
}

void TaskCenter::run()
{
    while (mbRun)
    {
        if (this->mTasks.size() > 0)
        {
            std::shared_ptr<FDTask> task = this->mTasks[0];
            this->mTasks.pop();

            task->execTask();
        }

        QThread::msleep(200);
    }
}
