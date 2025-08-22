#pragma once

template<class T>
class IObserver
{
public:
    virtual ~IObserver(){};
    virtual void OnCompleted() = 0;
    virtual void OnNext(T value) = 0;
};
