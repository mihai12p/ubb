#include "pch.h"
#include "Utils.h"

std::string
FiletimeToTimestamp(
    _In_ const FILETIME& Filetime
)
{
    SYSTEMTIME systemTime = { 0 };
    FileTimeToSystemTime(&Filetime, &systemTime);
    CHAR buffer[24] = { 0 };
    _snprintf_s(buffer, 24, _TRUNCATE, "%04d-%02d-%02d %02d:%02d:%02d.%03d", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
    return buffer;
}