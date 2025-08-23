#pragma once

#include <IDisposable.h>

class IInterface : public IDisposable
{
protected:
    virtual ~IInterface() = default;

public:
    virtual void Dispose() = 0;
};
