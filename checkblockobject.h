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

class CheckBlockThread : public QThread
{
public:
    explicit CheckBlockThread(HANDLE handle, QObject* parent = 0);

protected:
    void run() override;

private:
    HANDLE mCheckHandle;
};

#endif // CHECKBLOCKOBJECT_H
