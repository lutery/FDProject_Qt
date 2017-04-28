#ifndef UNLOCKTHREAD_H
#define UNLOCKTHREAD_H

#include <QThread>
#include <QString>

class UnlockThread : public QThread
{
    Q_OBJECT
public:
    explicit UnlockThread(QString filePath, QObject *parent = 0);

signals:
    void onUnlock(bool);

public slots:

protected:
    void run() override;

private:
    QString mFilePath;
};

#endif // UNLOCKTHREAD_H
