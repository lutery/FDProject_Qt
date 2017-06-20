#include "checkblockobject.h"
#include <QDebug>

//CheckBlockObject::CheckBlockObject(HANDLE handle, QObject* parent) : QObject(parent)
//{
//    Q_ASSERT(handle != NULL);
//    mCheckHandle = handle;
//}

//void CheckBlockObject::start()
//{
//    static NTQUERYINFORMATIONFILE fpNtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryInformationFile");

//    if (fpNtQueryInformationFile != NULL)
//    {
//        BYTE buf[1024];
//        IO_STATUS_BLOCK ioStatus;
//        fpNtQueryInformationFile(mCheckHandle, &ioStatus, buf, 1024, FileNameInformation);
//    }
//}

/**
 * @brief CheckBlockThread::CheckBlockThread
 * @param handle 待验证句柄
 * @param parent 父类QObject对象
 */
CheckBlockThread::CheckBlockThread(HANDLE handle, QObject *parent) : QThread(parent)
{
    Q_ASSERT(handle != NULL);
    mCheckHandle = handle;
}

/**
 * @brief CheckBlockThread::run 子线程执行主体
 */
void CheckBlockThread::run()
{
    // 获取NtQueryInformationFile函数指针
    static NTQUERYINFORMATIONFILE fpNtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryInformationFile");

    if (fpNtQueryInformationFile != NULL)
    {
        BYTE buf[1024];
        IO_STATUS_BLOCK ioStatus;
        qDebug() << "start check block query";
        // 如果句柄是管道句柄，那么这个函数将不会返回，卡住线程
        fpNtQueryInformationFile(mCheckHandle, &ioStatus, buf, 1024, FileNameInformation);
    }

    qDebug() << "end check block query";
}
