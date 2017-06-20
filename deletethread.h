#ifndef DELETETHREAD_H
#define DELETETHREAD_H

#include <QThread>

/**
 * @brief The DeleteThread class 删除文件线程
 */
class DeleteThread : public QThread
{
    Q_OBJECT
public:
    explicit DeleteThread(QString filePath, QObject *parent = 0);

signals:
    // 删除文件结果信号
    void onDelFile(bool);

public slots:

protected:
    void run() override;

private:
    // 需要删除的文件路径
    QString mFilePath;
};

#endif // DELETETHREAD_H
