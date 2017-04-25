#ifndef FDOBJECT_H
#define FDOBJECT_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>
#include <QStringList>
#include "predefine.h"

/**
 * @brief The FDObject class 解锁删除类
 */
class FDObject : public QObject
{
    Q_OBJECT
public:
    explicit FDObject(QObject *parent = 0);
    ~FDObject();

signals:
    // 分析完成信号，完整信息，具备完整的信息
    void analysisComplete(bool, QVector<std::shared_ptr<ncFileHandle>>);
    // 分析完成信号，简略信息，仅具备占用可执文件的路径信息
    void onComplete(bool, QStringList);

public slots:
    void analysis(QString filePath);
    void unlockHandle(QString filePathName);

private:
    // 分析是否完成
    bool mbAnalyse;
    // 存储所有的占用文件的信息
    QVector<std::shared_ptr<ncFileHandle>> mHandles;

    bool CloseRemoteHandle(DWORD dwProcessId, HANDLE hRemoteHandle);
};

#endif // FDOBJECT_H
