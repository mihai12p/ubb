#pragma once

#include <QtCore/qtypes.h>
#include "../domain/Process.hpp"

enum class ResponseType : qint16
{
    OK = 0,
    ERROR = 1,
    DENY = 2,

    MAX_RESPONSE_TYPE
};

class IResponse
{
public:
    explicit IResponse(ResponseType responseType) : responseType{ responseType } { }
    virtual ~IResponse() { }

    const ResponseType getResponseType() const
    {
        return this->responseType;
    }

    virtual const QString& GetData() const = 0;

    virtual void SetAdditionalData(const Process& additionalData) = 0;
    virtual const Process& GetAdditionalData() const = 0;

private:
    ResponseType responseType;
};

template <class T>
class Response : public IResponse
{
public:
    Response(ResponseType responseType, const T& data) : IResponse(responseType), data{ data } { }

    const QString& GetData() const override
    {
        return this->data;
    }

    void SetAdditionalData(const Process& additionalData) override
    {
        this->additionalData = additionalData;
    }

    const Process& GetAdditionalData() const override
    {
        return this->additionalData;
    }

private:
    T data;
    Process additionalData{ };
};