#ifndef CURSHFILETHREAD_H
#define CURSHFILETHREAD_H

#include <QThread>

/**
 * @brief The CurshFileThread class 粉碎文件线程
 */
class CurshFileThread : public QThread
{
    Q_OBJECT
public:
    explicit CurshFileThread(QString filePath, QObject *parent = 0);

signals:
    void onCurshFile(bool);

public slots:

protected:
    void run() override;

private:
    // 需要粉碎文件的路径
    QString mFilePath;
};

#endif // CURSHFILETHREAD_H
