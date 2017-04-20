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
//    fdObject.analysis("E:\\UBuntu1404.rar");
    fdObject.analysis("H:\\CloudMusic\\MONACA - クロイウタ／日本国外向け製品収録版.mp3");
    qDebug() << "end run";

    int i = 0;
    i += 1;
}
