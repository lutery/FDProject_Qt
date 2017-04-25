#include "fdobject.h"
#include "checkblockobject.h"
#include <string>
#include <QDebug>
#include <QThread>
#include <unordered_map>
#include <QStringList>

//class CheckBlockObject : public QObject
//{
//    Q_OBJECT
//public:
//    explicit CheckBlockObject(HANDLE handle, QObject* parent = 0) : QObject(parent)
//    {
//        Q_ASSERT(handle != NULL);
//        mCheckHandle = handle;
//    }

//public slots:
//    void start();

//private:
//    HANDLE mCheckHandle;
//};

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
 * @brief The FDObjectHelper class FDObject对象帮助类
 */
class FDObjectHelper : public QObject
{
    Q_OBJECT
public:
    static PSYSTEM_HANDLE_INFORMATION GetSystemHandleInfo()
    {
        static NTQUERYSYSTEMINFORMATION fpNtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQuerySystemInformation");

        if (fpNtQuerySystemInformation == NULL)
        {
            return NULL;
        }

        DWORD dwLength = 0;
        SYSTEM_HANDLE_INFORMATION shi;
        NTSTATUS status = fpNtQuerySystemInformation(SystemHandleInformation, &shi, sizeof(shi), &dwLength);
        if (status != STATUS_INFO_LENGTH_MISMATCH)
        {
            return NULL;
        }

        PSYSTEM_HANDLE_INFORMATION pshi = (PSYSTEM_HANDLE_INFORMATION)malloc(dwLength);
        while (true)
        {
            status = fpNtQuerySystemInformation(SystemHandleInformation, pshi, dwLength, &dwLength);
            if (status != STATUS_INFO_LENGTH_MISMATCH)
            {
                break;
            }

            pshi = (PSYSTEM_HANDLE_INFORMATION)realloc(pshi, dwLength);
        }

        if (!NT_SUCCESS(status))
        {
            free(pshi);
            pshi = NULL;
        }

        return pshi;
    }

    //
    // 检测指定句柄是否可能导致NtQueryObject卡死：
    //     1.注意必须使用NtQueryInformationFile而不是NtQueryObject进行检测，否则可能导致WinXP系统
    //       下进程死锁而无法结束。
    //
//    static void CheckBlockThreadFunc(void* param)
//    {
//        static NTQUERYINFORMATIONFILE fpNtQueryInformationFile =
//            (NTQUERYINFORMATIONFILE)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryInformationFile");

//        if (fpNtQueryInformationFile != NULL) {
//            BYTE buf[1024];
//            IO_STATUS_BLOCK ioStatus;
//            fpNtQueryInformationFile((HANDLE)param, &ioStatus, buf, 1024, FileNameInformation);
//        }
//    }

    /**
     * @brief IsBlockingHandle 判断是否是管道占用
     * @param handle 待判断的句柄
     * @return
     */
    static BOOL IsBlockingHandle(HANDLE handle)
    {
//        HANDLE hThread = (HANDLE)_beginthread(FDObjectHelper::CheckBlockThreadFunc, 0, (void*)handle);

//        if (WaitForSingleObject(hThread, 100) != WAIT_TIMEOUT) {
//            return FALSE;
//        }

//        TerminateThread(hThread, 0);
//        return TRUE;

//        QThread thread;
//        CheckBlockObject cbObject(handle);
//        cbObject.moveToThread(&thread);
//        QObject::connect(&thread, SIGNAL(started()), &cbObject, SLOT(start()));
        CheckBlockThread* thread = new CheckBlockThread(handle);
        // 连接线程执行完成信号与线程释放自身槽
        // Todo 这里可能存在内存泄漏，需要仔细的检查
        QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
//        QThread::msleep(500);

//        qDebug() << "start wait";
        // 这里等待1s，通常来说，如果是管道占用，这里基本不会返回
        // 如果超时，这里返回的是false
        if (!thread->wait(1000))
        {
//            qDebug() << "time out wait";
//            qDebug() << "        ";
            return TRUE;
        }

//        qDebug() << "end wait";
//        qDebug() << "        ";

        // 终端线程，等待执行结束
        thread->terminate();
        thread->wait();

        return FALSE;
    }

    /**
     * @brief GetDeviceDriveMap 获取设备路径与驱动路径之间的映射表
     * @param mapDeviceDrive 接收映射表map
     */
    static void GetDeviceDriveMap(std::unordered_map<tstring, tstring>& mapDeviceDrive)
    {
        TCHAR szDrives[512];
        // 枚举系统所有的逻辑驱动器，这边返回的是一个以空字符为分隔符的字符串
        if (!GetLogicalDriveStrings(_countof(szDrives) - 1, szDrives))
        {
            return;
        }

        TCHAR* lpDrives = szDrives;
        TCHAR szDevice[MAX_PATH];
        TCHAR szDrive[3] = _T(" :");
        do{
            *szDrive = *lpDrives;

            // 根据逻辑驱动器获取NT设备路径并存储起来
            if (QueryDosDevice(szDrive, szDevice, MAX_PATH))
            {
                mapDeviceDrive[szDevice] = szDrive;
            }

            // 遍历到下一个驱动器
            while(*lpDrives++);
        } while (*lpDrives);
    }

    /**
     * @brief DevicePathToDrivePath 将设备路径形式转换为驱动路径形式
     * @param path 设备路径形式的路径
     * @return 返回true表示转换成功，返回false表示转换失败
     */
    static BOOL DevicePathToDrivePath(tstring& path)
    {
        // 获取所有的设备路径映射到驱动路径的映射表
        static std::unordered_map<tstring, tstring> mapDeviceDrive;

        if (mapDeviceDrive.empty())
        {
            FDObjectHelper::GetDeviceDriveMap(mapDeviceDrive);
        }

        // 本来想用QHash，可视不支持tstring
//        QHashIterator<tstring, tstring> hashIter(mapDeviceDrive);
//        while (hashIter.hasNext())
//        {
//            hashIter.next();

//            size_t nLength = hashIter.key().length();
//            if (_tcsnicmp(hashIter.key().c_str(), path.c_str(), nLength) == 0)
//            {
//                path.replace(0, nLength, hashIter.value());
//                return TRUE;
//            }
//        }

        // 遍历映射表，替换路径形式
        for (std::unordered_multimap<tstring, tstring>::iterator iter = mapDeviceDrive.begin(); iter != mapDeviceDrive.end(); ++iter)
        {
            size_t nLength = iter->first.length();
            if (_tcsnicmp(iter->first.c_str(), path.c_str(), nLength) == 0)
            {
                path.replace(0, nLength, iter->second);
                return TRUE;
            }
        }

        return FALSE;
    }

    /**
     * @brief GetHandlePath 获取句柄的文件路径
     * @param handle 待获取路径的句柄
     * @param path 返回路径信息
     * @return 返回true表示获取成功，返回false表示获取失败
     */
    static BOOL GetHandlePath(HANDLE handle, tstring& path)
    {
        static NTQUERYOBJECT fpNtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryObject");

        if (fpNtQueryObject == NULL)
        {
            return FALSE;
        }

        DWORD dwLength = 0;
        OBJECT_NAME_INFORMATION info;
        // 获取需要的存储空间大小
        NTSTATUS status = fpNtQueryObject(handle, C_OBJECT_INFORMATION_CLASS::ObjectNameInformation, &info, sizeof(info), &dwLength);
        if (status != STATUS_BUFFER_OVERFLOW)
        {
            return FALSE;
        }

        POBJECT_NAME_INFORMATION pInfo = (POBJECT_NAME_INFORMATION)malloc(dwLength);
        while (true)
        {
            // 申请内存知道申请成功，申请的句柄信息为C_OBJECT_INFORMATION_CLASS::ObjectNameInformation
            status = fpNtQueryObject(handle, C_OBJECT_INFORMATION_CLASS::ObjectNameInformation, pInfo, dwLength, &dwLength);

            if (status != STATUS_BUFFER_OVERFLOW)
            {
                break;
            }

            pInfo = (POBJECT_NAME_INFORMATION)realloc(pInfo, dwLength);
        }

        BOOL bRes = FALSE;
        if (NT_SUCCESS(status))
        {
            // 获取路径信息，并转换为逻辑驱动器形式
            path = pInfo->Name.Buffer;
            bRes = FDObjectHelper::DevicePathToDrivePath(path);
        }

        free(pInfo);

        return bRes;
    }
};

FDObject::FDObject(QObject *parent) : QObject(parent)
{
    mbAnalyse = false;
}

FDObject::~FDObject()
{

}

/**
 * @brief FDObject::analysis
 * @param filePathName
 */
void FDObject::analysis(QString filePathName)
{
    mHandles.clear();
    mbAnalyse = false;

    if (filePathName.length() <= 0)
    {
        emit this->analysisComplete(false, mHandles);
        return;
    }

    ncScopedHandle hTempFile = CreateFile(_T("NUL"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
    if (hTempFile == NULL)
    {
        emit this->analysisComplete(false, mHandles);
        return;
    }

    PSYSTEM_HANDLE_INFORMATION pshi = FDObjectHelper::GetSystemHandleInfo();
    if (pshi == NULL)
    {
        emit this->analysisComplete(false, mHandles);
        return;
    }

    BYTE nFileType = 0;
    DWORD dwCrtPid = GetCurrentProcessId();

    for (DWORD i = 0; i < pshi->dwCount; ++i)
    {
        if (pshi->Handles[i].dwProcessId == dwCrtPid && hTempFile == (HANDLE)pshi->Handles[i].wValue)
        {
            nFileType = pshi->Handles[i].bObjectType;
            break;
        }
    }

    HANDLE hCrtProc = GetCurrentProcess();
    for (DWORD i = 0; i < pshi->dwCount; ++i)
    {
        if (pshi->Handles[i].bObjectType != nFileType)
        {
            continue;
        }

        ncScopedHandle handle = NULL;
        ncScopedHandle hProc = OpenProcess(PROCESS_DUP_HANDLE, FALSE, pshi->Handles[i].dwProcessId);
        if (hProc == NULL || !DuplicateHandle(hProc, (HANDLE)pshi->Handles[i].wValue, hCrtProc, &handle, 0, FALSE, DUPLICATE_SAME_ACCESS))
        {
            continue;
        }

        if (FDObjectHelper::IsBlockingHandle(handle))
        {
            continue;
        }

        tstring filePath;
        if (FDObjectHelper::GetHandlePath(handle, filePath) && filePath.find(filePathName.toStdWString()) != tstring::npos)
        {
            ncScopedHandle hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, pshi->Handles[i].dwProcessId);

            TCHAR szProcName[MAX_PATH];
            GetProcessImageFileName(hProcess, szProcName, MAX_PATH);
            tstring path(szProcName);
            FDObjectHelper::DevicePathToDrivePath(path);
            std::shared_ptr<ncFileHandle> pFh = std::shared_ptr<ncFileHandle>(new ncFileHandle(pshi->Handles[i], filePath, path));
//            std::wstring wstring = szProcName;
            qDebug() << "QDebug is " << QString::fromUtf16((const ushort*)path.c_str());
            mHandles.push_back(pFh);
        }
    }

    free(pshi);

    mbAnalyse = true;
    emit this->analysisComplete(true, mHandles);

    QStringList handlePathList;

    for (std::shared_ptr<ncFileHandle> pFH : mHandles)
    {
        handlePathList.append(QString::fromStdWString(pFH->_path.c_str()));
//        handlePathList.append(pFH->);
    }

    emit this->onComplete(true, handlePathList);

    return;
}

void FDObject::unlockHandle(QString filePathName)
{
    mHandles.clear();
    mbAnalyse = false;

    if (filePathName.length() <= 0)
    {
        return;
    }

    ncScopedHandle hTempFile = CreateFile(_T("NUL"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
    if (hTempFile == NULL)
    {
        return;
    }

    PSYSTEM_HANDLE_INFORMATION pshi = FDObjectHelper::GetSystemHandleInfo();
    if (pshi == NULL)
    {
        return;
    }

    BYTE nFileType = 0;
    DWORD dwCrtPid = GetCurrentProcessId();

    for (DWORD i = 0; i < pshi->dwCount; ++i)
    {
        if (pshi->Handles[i].dwProcessId == dwCrtPid && hTempFile == (HANDLE)pshi->Handles[i].wValue)
        {
            nFileType = pshi->Handles[i].bObjectType;
            break;
        }
    }

    HANDLE hCrtProc = GetCurrentProcess();
    for (DWORD i = 0; i < pshi->dwCount; ++i)
    {
        if (pshi->Handles[i].bObjectType != nFileType)
        {
            continue;
        }

        ncScopedHandle handle = NULL;
        ncScopedHandle hProc = OpenProcess(PROCESS_DUP_HANDLE, FALSE, pshi->Handles[i].dwProcessId);
        if (hProc == NULL || !DuplicateHandle(hProc, (HANDLE)pshi->Handles[i].wValue, hCrtProc, &handle, 0, FALSE, DUPLICATE_SAME_ACCESS))
        {
            continue;
        }

        if (FDObjectHelper::IsBlockingHandle(handle))
        {
            continue;
        }

        tstring filePath;
        if (FDObjectHelper::GetHandlePath(handle, filePath) && filePath.find(filePathName.toStdWString()) != tstring::npos)
        {
//            ncScopedHandle hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, pshi->Handles[i].dwProcessId);

//            TCHAR szProcName[MAX_PATH];
//            GetProcessImageFileName(hProcess, szProcName, MAX_PATH);
//            tstring path(szProcName);
//            FDObjectHelper::DevicePathToDrivePath(path);
//            std::shared_ptr<ncFileHandle> pFh = std::shared_ptr<ncFileHandle>(new ncFileHandle(pshi->Handles[i], filePath, path));
//            qDebug() << "QDebug is " << QString::fromUtf16((const ushort*)path.c_str());
//            mHandles.push_back(pFh);
            if (handle != INVALID_HANDLE_VALUE)
            {
                CloseHandle(handle);
            }

            DuplicateHandle(hProc, (HANDLE)pshi->Handles[i].wValue, hCrtProc, &handle, 0, FALSE, DUPLICATE_CLOSE_SOURCE);

            if (handle != INVALID_HANDLE_VALUE)
            {
                CloseHandle(handle);
            }

            this->CloseRemoteHandle(pshi->Handles[i].dwProcessId, (HANDLE)pshi->Handles[i].wValue);
        }


        if (hProc != NULL)
        {
            CloseHandle(hProc);
        }
    }

    free(pshi);

    mbAnalyse = true;

    return;
}

/**
 * @brief FDObject::CloseRemoteHandle
 * @param dwProcessId 占用文件的进程
 * @param hRemoteHandle 占用文件进程的内部文件 句柄
 * @return
 */
bool FDObject::CloseRemoteHandle(DWORD dwProcessId, HANDLE hRemoteHandle)
{
    HANDLE hExecutHandle = NULL;
    BOOL bFlag = FALSE;
    HANDLE hProcess = NULL;
    HMODULE hKernel32Module = NULL;

    hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwProcessId);

    if (NULL == hProcess)
    {
        bFlag = FALSE;
        goto ErrorExit;
    }

    hKernel32Module = LoadLibraryW(L"kernel32.dll");

    if (hKernel32Module == NULL)
    {
        goto ErrorExit;
    }

    hExecutHandle = CreateRemoteThread(hProcess, 0, 0, (DWORD (__stdcall *)(void *))GetProcAddress(hKernel32Module, "CloseHandle"), hRemoteHandle, 0, NULL);

    if (NULL == hExecutHandle)
    {
        bFlag = FALSE;
        goto ErrorExit;
    }

    if (WaitForSingleObject(hExecutHandle, 2000) == WAIT_OBJECT_0)
    {
        bFlag = TRUE;
        goto ErrorExit;
    }
    else
    {
        bFlag = FALSE;
        goto ErrorExit;
    }

ErrorExit:

    if (hExecutHandle != NULL)
    {
        CloseHandle(hExecutHandle);
    }

    if (hProcess != NULL)
    {
        CloseHandle(hProcess);
    }

    if (hKernel32Module != NULL)
    {
        FreeLibrary(hKernel32Module);
    }

    return bFlag;
}
