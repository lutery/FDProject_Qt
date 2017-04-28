#ifndef FDSERVICE_H
#define FDSERVICE_H

#include <QObject>

class FDObject;
class AnalysisThread;
class UnlockThread;

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
    void complete(QStringList filePaths);
    void unlock(bool bunlock);
    void delcomplete(bool bdelete);
    void crush(bool bcrush);

public slots:
    void analysis(QString filePath);
    void unlockHandle(QString filePath);
    void deleteFile(QString filePath);
    void curshFile(QString filePath);
    void analysisComplete(bool isReady, QStringList filePaths);

private:
    // 删除解锁Object执行体
    FDObject* mpFDObject;
    // 分析子线程
    AnalysisThread* mpAnalysis;
    // 解锁子线程
    UnlockThread* mpUnlock;
};

#endif // FDSERVICE_H
