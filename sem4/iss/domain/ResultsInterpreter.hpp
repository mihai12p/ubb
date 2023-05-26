#pragma once

#include "Action.hpp"
#include "Process.hpp"

class ResultsInterpreter : public Action<qint32>
{
public:
    ResultsInterpreter() : Action(0) { };

    ResultsInterpreter(const Process& selectedProcess) : Action(0), selectedProcess(selectedProcess) { }

    void TakeAction();

private:
    void KillProcess();

private:
    Process selectedProcess{ };
};