#pragma once

template<class T>
class ICommand
{
public:
    virtual ~ICommand() { }
    virtual void Execute(T parameter) = 0;
};
