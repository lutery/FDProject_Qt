#ifndef TASKCENTER_H
#define TASKCENTER_H

#include <QThread>
#include <queue>
#include <memory>
#include <mutex>

class FDTask;

class TaskCenter : public QThread
{
    Q_OBJECT
public:
    explicit TaskCenter(QObject *parent = nullptr);

signals:

public slots:
   void quit();
   void pushTask(std::shared_ptr<FDTask> pTask);

protected:
    void run() override;

private:
    bool mbRun;
    std::mutex mTaskLock;
    std::queue<std::shared_ptr<FDTask>> mTasks;
};

#endif // TASKCENTER_H
