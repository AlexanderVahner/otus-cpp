#include <functional>
#include <system/IDisposable.h>

class Disposable : public IDisposable
{
private:
    std::function<void()> onDispose;
public:
    Disposable(std::function<void()> onDispose) : onDispose(onDispose) { }
    ~Disposable() { delete this; }

    void Dispose() override
    {
        onDispose();
        delete this;
    }
};
