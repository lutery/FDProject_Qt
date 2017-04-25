#ifndef CHECKBLOCKOBJECT_H
#define CHECKBLOCKOBJECT_H

//#include <QObject>
#include <QThread>
#include "predefine.h"

//class CheckBlockObject : public QObject
//{
//    Q_OBJECT
//public:
//    explicit CheckBlockObject(HANDLE handle, QObject* parent = 0);

//public slots:
//    void start();

//private:
//    HANDLE mCheckHandle;
//};

/**
 * @brief The CheckBlockThread class 判断是否是管道占用线程
 */
class CheckBlockThread : public QThread
{
public:
    explicit CheckBlockThread(HANDLE handle, QObject* parent = 0);

protected:
    void run() override;

private:
    // 待判断的句柄
    HANDLE mCheckHandle;
};

#endif // CHECKBLOCKOBJECT_H
