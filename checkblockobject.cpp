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

CheckBlockThread::CheckBlockThread(HANDLE handle, QObject *parent) : QThread(parent)
{
    Q_ASSERT(handle != NULL);
    mCheckHandle = handle;
}

void CheckBlockThread::run()
{
    static NTQUERYINFORMATIONFILE fpNtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryInformationFile");

    if (fpNtQueryInformationFile != NULL)
    {
        BYTE buf[1024];
        IO_STATUS_BLOCK ioStatus;
//        qDebug() << "start query";
        fpNtQueryInformationFile(mCheckHandle, &ioStatus, buf, 1024, FileNameInformation);
    }

//    qDebug() << "end query";
}
