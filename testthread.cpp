#include "testthread.h"
#include "checkblockobject.h"
#include "fdobject.h"
#include <QDebug>

//TestThread::TestThread()
//{

//}

void TestThread::run()
{
    FDObject fdObject;
    qDebug() << "start run";
    fdObject.analysis("E:\\Program Files\\AutoHotkey\\myScript\\MyHotKey.zip");
    qDebug() << "end run";

    int i = 0;
    i += 1;
}
