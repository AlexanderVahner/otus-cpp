#include <list>
#include <system/IObservable.h>
#include <system/IObserver.h>
#include "Disposable.cpp"

template<class T>
class Observable : public IObservable<T>, public IDisposable
{
private:
    std::list<IObserver<T>*> observers;

public:
    Observable()
    {
        //observers = new std::list<IObserver<T>*>();
    }

    ~Observable() = default;

    IDisposable* Subscribe(IObserver<T>* observer) override
    {
        observers.push_back(observer);
        return new Disposable([this, observer]() { observers.remove(observer); });
    }

    void Publish(T value)
    {
        for (auto observer: observers)
        {
            observer->OnNext(value);
        }
    }

    void Dispose() override
    {
        for (auto observer: observers)
        {
            observer->OnCompleted();
        }
        observers.clear();
        delete this;
    }
};
