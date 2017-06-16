#ifndef PREDEFINE_H
#define PREDEFINE_H
#include <tchar.h>
#include <Windows.h>

#include <string>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> tstring;

#include <winternl.h>

#include <psapi.h>

#define NT_SUCCESS(status)					(status == (NTSTATUS)0x00000000L)
#define STATUS_INFO_LENGTH_MISMATCH			((NTSTATUS)0xC0000004L)
#define STATUS_BUFFER_OVERFLOW				((NTSTATUS)0x80000005L)
#define SystemHandleInformation				((SYSTEM_INFORMATION_CLASS)16)


// NTQUERYOBJECT
typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING Name;
    WCHAR NameBuffer[1];
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef enum class C_OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation
} COBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

using NTQUERYOBJECT = NTSTATUS(WINAPI *)(_In_opt_ HANDLE Handle,
                                         _In_ COBJECT_INFORMATION_CLASS ObjectInformationClass,
                                         _Out_opt_ PVOID ObjectInformation,
                                         _In_ ULONG ObjectInformationLength,
                                         _Out_opt_ PULONG ReturnLength);

// NTQUERYSYSTEMINFORMATION
typedef struct _SYSTEM_HANDLE {
    DWORD dwProcessId;
    BYTE bObjectType;
    BYTE bFlags;
    WORD wValue;
    PVOID pAddress;
    DWORD GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION {
    DWORD dwCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

using NTQUERYSYSTEMINFORMATION = NTSTATUS(WINAPI *)(
                                                    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
                                                    OUT PVOID SystemInformation,
                                                    IN ULONG SystemInformationLength,
                                                    OUT PULONG ReturnLength OPTIONAL);

using NTQUERYINFORMATIONFILE = NTSTATUS(WINAPI*)(IN HANDLE FileHandle,
                                                 OUT PIO_STATUS_BLOCK IoStatusBlock,
                                                 OUT PVOID FileInformation,
                                                 IN ULONG Length,
                                                 IN FILE_INFORMATION_CLASS FileInformationClass);

//
// NtQueryInformationFile
//
#define FileNameInformation					((FILE_INFORMATION_CLASS)9)

//typedef NTSTATUS(WINAPI *NTQUERYSYSTEMINFORMATION)(
//	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
//	OUT PVOID SystemInformation,
//	IN ULONG SystemInformationLength,
//	OUT PULONG ReturnLength OPTIONAL);

// ncScopedHandle
class ncScopedHandle
{
    ncScopedHandle(const ncScopedHandle&);
    ncScopedHandle& operator=(const ncScopedHandle&);
public:
    ncScopedHandle(HANDLE handle)
        : _handle(handle)
    {
    }

    ~ncScopedHandle()
    {
        if (_handle != NULL) {
            CloseHandle(_handle);
        }
    }

    operator HANDLE() const
    {
        return _handle;
    }

    PHANDLE  operator& ()
    {
        return &_handle;
    }

    void operator=(HANDLE handle)
    {
        if (_handle != NULL) {
            CloseHandle(_handle);
        }
        _handle = handle;
    }

private:
    HANDLE _handle;
};

struct ncFileHandle
{
    SYSTEM_HANDLE	_handle;
    tstring			_filePath;
    tstring			_path;

    ncFileHandle(SYSTEM_HANDLE handle, const tstring& filePath, const tstring& path)
        : _handle(handle)
        , _filePath(filePath)
        , _path(path)
    {
    }
};

template<class T>
void stopThread(T& myThread)
{
    if (myThread != nullptr && myThread->isRunning())
    {
        myThread->quit();
        myThread->terminate();
        myThread->wait();
        delete myThread;
        myThread = nullptr;
    }
}

#endif // PREDEFINE_H
