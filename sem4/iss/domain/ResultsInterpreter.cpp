#include "ResultsInterpreter.hpp"
#include <Windows.h>

void ResultsInterpreter::TakeAction()
{
    switch (this->selectedProcess.getAction())
    {
    case 0:
    case 1:
        break;
    case 2:
        this->KillProcess();
        break;
    default:
        break;
    }
}

void ResultsInterpreter::KillProcess()
{
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, this->selectedProcess.getPID());
    if (processHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    TerminateProcess(processHandle, 0);
    CloseHandle(processHandle);
}