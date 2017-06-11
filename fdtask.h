#ifndef FDTASK_H
#define FDTASK_H

#include <QObject>

class FDTask : public QObject
{
    Q_OBJECT
public:
    explicit FDTask(QObject *parent = nullptr);

signals:

public slots:
    virtual void execTask();

public:
    int getTaskID();
    void setTaskID(int taskid);

private:
    int mTaskID;
};

#endif // FDTASK_H
