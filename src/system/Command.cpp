#include <functional>
#include <ICommand.h>
#include <IDisposable.h>

template<class T>
class Command : public ICommand<T>, public IDisposable
{
private:
    std::function<void(T)> execute;

public:
    Command(std::function<void(T)> execute) : execute(execute)
    {

    }

    ~Command() = default;

    void Execute(T parameter) override
    {
        if (execute)
        {
            execute(parameter);
        }
    }

    void Dispose() override
    {
        delete this;
    }
};
