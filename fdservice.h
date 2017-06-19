#ifndef FDSERVICE_H
#define FDSERVICE_H

#include <QObject>

class FDObject;
class AnalysisThread;
class UnlockThread;
class DeleteThread;
class CurshFileThread;
class TaskCenter;

/**
 * @brief The FDService class 解锁删除服务
 */
class FDService : public QObject
{
    Q_OBJECT
public:
    explicit FDService(QObject *parent = 0);
    ~FDService();

signals:
    // 查询完成信号
    void sigComplete(QStringList filePaths);
    void sigUnlock(bool bunlock);
    void sigDelcomplete(bool bdelete);
    void sigCrush(bool bcrush);

public slots:
    void sltAnalysis(QString filePath);
    void sltUnlockHandle(QString filePath);
    void sltDeleteFile(QString filePath);
    void sltCurshFile(QString filePath);
    void sltAnaComplete(bool isReady, QStringList filePaths);

private:
    // 删除解锁Object执行体
//    FDObject* mpFDObject;
//    // 分析子线程
//    AnalysisThread* mpAnalysis;
//    // 解锁子线程
//    UnlockThread* mpUnlock;
//    // 删除子线程
//    DeleteThread* mpTDelete;
//    // 粉碎子线程
//    CurshFileThread* mpTCursh;
    // 任务中心
    TaskCenter* mpTaskCenter;
};

#endif // FDSERVICE_H
