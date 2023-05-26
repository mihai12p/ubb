#include "Process.hpp"
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

QX_REGISTER_CPP_EXPORT_DLL(Process)

namespace qx
{
template <>
void register_class(QxClass<Process>& t)
{
    t.id(&Process::id, "id");
    t.data(&Process::PID, "PID");
    t.data(&Process::name, "processName");
    t.data(&Process::action, "processAction");
}
}

const QList<QString> Process::getDetails()
{
    QList<QString> details{ };

    details.append("Process ID: " + QString::number(this->PID));
    details.append("Parent process ID: " + QString::number(this->ParentPID));

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, this->PID);
    if (processHandle == INVALID_HANDLE_VALUE)
    {
        return details;
    }

    WCHAR processPath[MAX_PATH] = { 0 };
    DWORD processPathSize = MAX_PATH;
    BOOL status = QueryFullProcessImageNameW(processHandle, 0, processPath, &processPathSize);
    if (!status)
    {
        details.append("Last error code: " + QString::number(GetLastError()));
        CloseHandle(processHandle);
        return details;
    }

    details.append("Process path: " + QString::fromWCharArray(processPath, wcslen(processPath)));

    DWORD sizeNeeded = 0;
    HMODULE modules[1024] = { 0 };
    if (EnumProcessModules(processHandle, modules, sizeof(modules), &sizeNeeded))
    {
        details.append("Modules:");
        for (int i = 0; i < (sizeNeeded / sizeof(HMODULE)); ++i)
        {
            WCHAR moduleName[MAX_PATH] = { 0 };
            GetModuleFileNameEx(processHandle, modules[i], moduleName, sizeof(moduleName) / sizeof(WCHAR));
            details.append("        " + QString::fromWCharArray(moduleName, wcslen(moduleName)));
        }
    }
    else
    {
        details.append("Last error code: " + QString::number(GetLastError()));
    }

    CloseHandle(processHandle);
    return details;
}