#pragma once

#include <IObserver.h>
#include <IDisposable.h>

template<class T>
class IObservable {
public:
    virtual ~IObservable(){};
    virtual IDisposable* Subscribe(IObserver<T> *observer) = 0;
};
