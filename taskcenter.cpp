#include "taskcenter.h"
#include "fdtask.h"

TaskCenter::TaskCenter(QObject *parent) : QThread(parent)
{
    this->mbRun = true;
}

void TaskCenter::quit()
{
    this->mbRun = false;

    this->mTaskLock.lock();
    this->mTasks.empty();
    this->mTaskLock.unlock();
}

void TaskCenter::pushTask(std::shared_ptr<FDTask> pTask)
{
    this->mTaskLock.lock();
    this->mTasks.push(pTask);
    this->mTaskLock.unlock();
}

void TaskCenter::run()
{
    while (mbRun)
    {
        if (this->mTaskLock.try_lock() && this->mTasks.size() > 0)
        {
            std::shared_ptr<FDTask> task = this->mTasks.front();
            this->mTasks.pop();

            this->mTaskLock.unlock();
            task->execTask();

        }

        QThread::msleep(200);
    }
}
