#pragma once

#include <QtCore/qtypes.h>

enum class RequestType : qint16
{
    LOGIN = 0,
    LOGOUT = 1,
    TAKE_ACTION = 2,

    MAX_REQUEST_TYPE
};

class IRequest
{
public:
    explicit IRequest(RequestType requestType) : requestType{ requestType } { }

    const RequestType getRequestType() const
    {
        return this->requestType;
    }

private:
    RequestType requestType;
};

template <class T>
class Request : public IRequest
{
public:
    Request(RequestType requestType, const T& data) : IRequest(requestType), data{ data } { }

    const T& GetData() const
    {
        return this->data;
    }

private:
    T data;
};