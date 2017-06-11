#ifndef TASKCENTER_H
#define TASKCENTER_H

#include <QThread>
#include <queue>
#include <memory>

class FDTask;

class TaskCenter : public QThread
{
    Q_OBJECT
public:
    explicit TaskCenter(QObject *parent = nullptr);

signals:

public slots:


protected:
    void run() override;

private:
    bool mbRun;
    std::queue<std::shared_ptr<FDTask>> mTasks;
};

#endif // TASKCENTER_H
