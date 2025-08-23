#pragma once

class IDisposable
{
protected:
    virtual ~IDisposable() = default;

public:
    virtual void Dispose() = 0;

    IDisposable& operator=(const IDisposable&) = delete;
};
