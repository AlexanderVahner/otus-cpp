#include <functional>
#include <system/IObserver.h>

template<class T>
class Observer : public IObserver<T>
{
private:
    std::function<void(T)> onNext;
    std::function<void()> onCompleted;
public:
    Observer(std::function<void(T)> onNext, std::function<void()> onCompleted = nullptr)
        : onNext(onNext), onCompleted(onCompleted)
    {

    }

    ~Observer() = default;

    void OnCompleted() override
    {
        if (onCompleted) onCompleted();
    }

    void OnNext(T value) override
    {
        onNext(value);
    }
};
