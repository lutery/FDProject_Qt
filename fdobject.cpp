#include "fdobject.h"
#include "predefine.h"
#include <QThread>
#include <QHash>
#include <QHashIterator>

class CheckBlockObject : QObject
{
    Q_OBJECT
public:
    explicit CheckBlockObject(HANDLE handle, QObject* parent = 0) : QObject(parent)
    {
        Q_ASSERT(handle != NULL);
        mCheckHandle = handle;
    }

public slots:
    void start()
    {
        static NTQUERYINFORMATIONFILE fpNtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryInformationFile");

        if (fpNtQueryInformationFile != NULL)
        {
            BYTE buf[1024];
            IO_STATUS_BLOCK ioStatus;
            fpNtQueryInformationFile(mCheckHandle, mCheckHandle, buf, 1024, FileNameInformation);
        }
    }

private:
    HANDLE mCheckHandle;
};

class FDObjectHelper
{
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

    static BOOL IsBlockingHandle(HANDLE handle)
    {
        QThread thread;
        CheckBlockObject cbObject(handle);
        cbObject.moveToThread(&thread);
        QObject::connect(&thread, SIGNAL(started()), &cbObject, SLOT(start()));
        thread.start();

        if (!thread.wait(100))
        {
            return FALSE;
        }

        thread.terminate();
        thread.wait();

        return TRUE;
    }

    static void GetDeviceDriveMap(QHash<tstring, tstring>& mapDeviceDrive)
    {
        TCHAR szDrives[512];
        if (!GetLogicalDriveStrings(_countof(szDrives) - 1, szDrives))
        {
            return;
        }

        TCHAR* lpDrives = szDrives;
        TCHAR szDevice[MAX_PATH];
        TCHAR szDrive[3] = _T(" :");
        do{
            *szDrive = *lpDrives;

            if (QueryDosDevice(szDrive, szDevice, MAX_PATH))
            {
                mapDeviceDrive[szDevice] = szDrive;
            }

            while(*lpDrives++);
        } while (*lpDrives);
    }

    static BOOL DevicePathToDrivePath(tstring& path)
    {
        static QHash<tstring, tstring> mapDeviceDrive;

        if (mapDeviceDrive.empty())
        {
            FDObjectHelper::GetDeviceDriveMap(mapDeviceDrive);
        }

        QHashIterator<tstring, tstring> hashIter(mapDeviceDrive);
        while (hashIter.hasNext())
        {
            hashIter.next();

            size_t nLength = hashIter.key().length();
            if (_tcsnicmp(hashIter.key().c_str(), path.c_str(), nLength) == 0)
            {
                path.replace(0, nLength, hashIter.value());
                return TRUE;
            }
        }

        return FALSE;
    }

    static BOOL GetHandlePath(HANDLE handle, tstring& path)
    {
        static NTQUERYOBJECT fpNtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQueryObject");

        if (fpNtQueryObject == NULL)
        {
            return FALSE;
        }

        DWORD dwLength = 0;
        OBJECT_NAME_INFORMATION info;
        NTSTATUS status = fpNtQueryObject(handle, C_OBJECT_INFORMATION_CLASS::ObjectNameInformation, &info, sizeof(info), &dwLength);
        if (status != STATUS_BUFFER_OVERFLOW)
        {
            return FALSE;
        }

        POBJECT_NAME_INFORMATION pInfo = (POBJECT_NAME_INFORMATION)malloc(dwLength);
        while (true)
        {
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
            path = pInfo->Name.Buffer;
            bRes = FDObjectHelper::DevicePathToDrivePath(path);
        }

        free(pInfo);

        return bRes;
    }
};

FDObject::FDObject(QObject *parent) : QObject(parent)
{

}

FDObject::~FDObject()
{

}

void FDObject::analysis(QString filePathName)
{
    mHandles.clear();

    if (filePathName.length() <= 0)
    {
        return;
    }

    ncScopedHandle hTempFile = CreateFile(_T("NUL"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
    if (hTempFile == NULL)
    {
        return FALSE;
    }

    PSYSTEM_HANDLE_INFORMATION pshi = FDObjectHelper::GetSystemHandleInfo();
    if (pshi == NULL)
    {
        return FALSE;
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
        if (FDObjectHelper::GetHandlePath(handle, filePath) && filePath.find(filePathName.c_str()) != tstring::npos)
        {
            ncScopedHandle hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, pshi->Handles[i].dwProcessId);

            TCHAR szProcName[MAX_PATH];
            GetProcessImageFileName(hProcess, szProcName, MAX_PATH);
            tstring path(szProcName);
            FDObjectHelper::DevicePathToDrivePath(path);
            std::shared_ptr<ncFileHandle> pFh = std::shared_ptr<ncFileHandle>(new ncFileHandle(pshi->Handles[i], filePath, path));
            mHandles.push_back(pFh);
        }
    }

    free(pshi);

    return TRUE;
}
