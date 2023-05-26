#include "Scan.hpp"
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

void FullScan::PerformScan()
{
    QList<Process> processes{ };

    HANDLE snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    PROCESSENTRY32W pe32{ };
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(snapHandle, &pe32))
    {
        CloseHandle(snapHandle);
        return;
    }

    do
    {
        Process process(pe32.th32ProcessID, pe32.th32ParentProcessID, QString::fromWCharArray(pe32.szExeFile, wcslen(pe32.szExeFile)));
        processes.append(process);
    } while (Process32NextW(snapHandle, &pe32));

    CloseHandle(snapHandle);
    this->setResults(processes);
}