#pragma once

#include <QtCore/qtypes.h>

enum class ResponseType : qint16
{
    OK = 0,
    ERROR = 1,

    MAX_RESPONSE_TYPE
};

class IResponse
{
public:
    explicit IResponse(ResponseType responseType) : responseType{ responseType } { }

    const ResponseType getResponseType() const
    {
        return this->responseType;
    }

private:
    ResponseType responseType;
};

template<class T>
class Response : public IResponse
{
public:
    Response(ResponseType responseType, const T& data) : IResponse(responseType), data{ data } { }

    const T& GetData() const
    {
        return this->data;
    }

private:
    T data;
};