#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

class TestThread : public QThread
{
//public:
//    TestThread();

protected:
    void run() override;
};

#endif // TESTTHREAD_H
