#pragma once

#include "Action.hpp"
#include "Process.hpp"

class Scan : public Action<qint32>
{
public:
    Scan() : Action(0) { };
    virtual ~Scan() { }

    const QList<Process>& getResults() const
    {
        return this->results;
    }

    void setResults(const QList<Process>& results)
    {
        this->results = results;
    }

    virtual void PerformScan() = 0;

private:
    QList<Process> results{ };
};

class FullScan : public Scan
{
public:
    void PerformScan() override;
};

class QuickScan : public Scan
{
public:
    void PerformScan() override { }
};